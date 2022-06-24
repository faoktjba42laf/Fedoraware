#include "Pong.h"
#include "../Menu.h"
#include "../../Fedworking/Fedworking.h"

enum MessageType {
	Broadcast,
	Handshake,
	Update
};

enum class GameState {
	None,
	Hosting,
	Joining,
	Match
};

static int PlayerID = Utils::RandInt(100, 999);
static GameState CurrentState = GameState::None;
static bool IsMultiplayer = false;

void CPong::Render()
{
	if (!IsOpen) { return; }

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.f, 0.f, 0.f, 1.f));
	ImGui::SetNextWindowSize({ WindowSize.x, WindowSize.y });
	
	if (ImGui::Begin("Pong", &IsOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		if (CurrentState != GameState::Match)
		{
			DrawMenu();
		} else if (CurrentState == GameState::Match)
		{
			DrawGame();
			UpdateGame();
			CheckCollisions();
			UpdateInput();

			// Reset if one player winds
			if (PlayerScore >= 10 || EnemyScore >= 10)
			{
				Init();
				I::Engine->ClientCmd_Unrestricted("play ui/duel_challenge");
			}
		}
	}
	ImGui::End();

	ImGui::PopStyleColor();
}

void CPong::ReceiveData(const std::vector<std::string>& dataVector)
{

}

/* Draw the main menu */
void CPong::DrawMenu()
{
	if (CurrentState == GameState::None)
	{
		if (ImGui::Button("Singleplayer"))
		{
			Init();
			CurrentState = GameState::Match;
			IsMultiplayer = false;
		}

		if (Vars::Misc::PartyNetworking.Value)
		{
			if (ImGui::Button("Host Match"))
			{
				CurrentState = GameState::Hosting;
				IsMultiplayer = true;
			}

			if (ImGui::Button("Join Math"))
			{
				CurrentState = GameState::Joining;
				IsMultiplayer = true;
			}
		} else
		{
			ImGui::Text("Enable 'Party Networking' to play online!");
		}
	} else
	{
		if (CurrentState == GameState::Hosting)
		{
			ImGui::Text("Hosting match in your party...");
		}

		if (CurrentState == GameState::Joining)
		{
			ImGui::Text("Searching for match in your party...");
		}

		if (ImGui::Button("Cancel"))
		{
			CurrentState = GameState::None;
			IsMultiplayer = false;
		}
	}
}

/* Draws the players, ball and scores */
void CPong::DrawGame()
{
	const auto drawList = ImGui::GetWindowDrawList();
	const auto windowPos = ImGui::GetWindowPos();

	// Draw Player
	drawList->AddRectFilled({ windowPos.x + XOffset, windowPos.y + PlayerY - (0.5f * RacketSize.y) },
		{ windowPos.x + XOffset + RacketSize.x, windowPos.y + PlayerY + (0.5f * RacketSize.y) },
		ImColor(255, 255, 255));

	// Draw Enemy
	drawList->AddRectFilled({ windowPos.x + (WindowSize.x - XOffset), windowPos.y + EnemyY - (0.5f * RacketSize.y) },
		{ windowPos.x + (WindowSize.x - XOffset - RacketSize.x), windowPos.y + EnemyY + (0.5f * RacketSize.y) },
		ImColor(255, 255, 255));

	// Draw Ball
	drawList->AddCircleFilled({ windowPos.x + BallPos.x, windowPos.y + BallPos.y },
		BallSize,
		ImColor(255, 255, 255));

	// Draw Scores
	drawList->AddText({ windowPos.x + XOffset, windowPos.y + 30.f }, ImColor(255, 255, 255), std::to_string(PlayerScore).c_str());
	drawList->AddText({ windowPos.x + (WindowSize.x - XOffset), windowPos.y + 30.f }, ImColor(255, 255, 255), std::to_string(EnemyScore).c_str());
}

/* Updates game movements every 5ms */
void CPong::UpdateGame()
{
	static Timer updateTimer{ };
	if (updateTimer.Run(5))
	{
		BallPos += BallVelocity * std::max(BallMultiplier, 1.f);
		EnemyY += EnemyVelocity;
		PlayerY += PlayerVelocity;

		Math::Clamp(EnemyY, 25.f, WindowSize.y);
		Math::Clamp(PlayerY, 25.f, WindowSize.y);
	}
}

/* Checks for collisions with borders and rackets */
void CPong::CheckCollisions()
{
	// X-Walls (Loss)
	if (BallPos.x + BallSize >= WindowSize.x)
	{
		PlayerScore++;
		BallMultiplier -= 0.02f;
		Reset();
	}
	else if (BallPos.x - BallSize <= 0.f)
	{
		EnemyScore++;
		BallMultiplier -= 0.04f;
		Reset();
	}

	// Y-Walls (Bounce)
	if (BallPos.y - 25.f - BallSize <= 0.f)
	{
		BallVelocity.y = 1.f;
	}
	else if (BallPos.y + BallSize >= WindowSize.y)
	{
		BallVelocity.y = -1.f;
	}

	// Enemy
	if (BallPos.x + BallSize >= WindowSize.x - XOffset - RacketSize.x
		&& BallPos.y - BallSize < EnemyY + (0.5f * RacketSize.y) && BallPos.y + BallSize > EnemyY - (0.5f * RacketSize.y))
	{
		if (BallVelocity.x > 0)
		{
			I::Engine->ClientCmd_Unrestricted("play ui/cyoa_switch");
		}
		BallVelocity.x = -1.f;
	}

	// Player
	if (BallPos.x - BallSize <= XOffset + RacketSize.x
		&& BallPos.y - BallSize < PlayerY + (0.5f * RacketSize.y) && BallPos.y + BallSize > PlayerY - (0.5f * RacketSize.y))
	{
		if (BallVelocity.x < 0)
		{
			I::Engine->ClientCmd_Unrestricted("play ui/cyoa_switch");
		}
		BallVelocity.x = 1.f;
		BallMultiplier += 0.02f;
	}
}

/* Updates the player and AI controllers */
void CPong::UpdateInput()
{
	const auto windowPos = ImGui::GetWindowPos();
	const auto cursorPos = ImGui::GetMousePos();

	// Enemy controller
	if (BallPos.y > EnemyY)
	{
		EnemyVelocity = 1.f;
	}
	else if (BallPos.y < EnemyY)
	{
		EnemyVelocity = -1.f;
	}
	else
	{
		EnemyVelocity = 0.f;
	}

	// Player controller
	if (cursorPos.y - windowPos.y < PlayerY)
	{
		PlayerVelocity = -1.f;
	}
	else if (cursorPos.y - windowPos.y > PlayerY)
	{
		PlayerVelocity = 1.f;
	}
	else
	{
		PlayerVelocity = 0.f;
	}
}

/* Initializes a new game */
void CPong::Init()
{
	PlayerScore = 0;
	EnemyScore = 0;
	PlayerY = 200.f;
	EnemyY = 200.f;
	BallPos = { 300.f, 200.f };
	BallVelocity = { 1.f, -1.f };
}

/* Resets the ball and players */
void CPong::Reset()
{
	BallPos = { 300.f, 200.f };
	BallVelocity = { 1.f, -1.f };
	I::Engine->ClientCmd_Unrestricted("play ui/chat_display_text");
}
