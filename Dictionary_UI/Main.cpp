#include "Header.h"
Color toolbarColor = { 29, 42, 87, 255 };
Color searchBarColor = { 15, 23, 59, 255 };

int main() {
	int screenWidth = 900;
	int screenHeight = 900;
	InitWindow(screenWidth, screenHeight, "Dictionary");
	float pageMarginLeft = 50;
	float pageMarginTop = 10;
	float margin = 50;
	int mode = 0; // 0: search, 1: insert, 2: delete, 3: help, 4: contact

	//for icons
	int iconSize = 50;
	float iconPosX = pageMarginLeft;  // X position
	float iconPosY = pageMarginTop;  // Y position
	float iconBoxWidth = 60; // Width of the rectangle
	float iconBoxHeight = 60; // Height of the rectangle
	int borderThickness = 3; // Thickness of the border
	Rectangle toolBarBackground = { 0, 0, screenWidth, iconBoxHeight + margin / 2 };
	vector<Texture2D> icons;
	icons.push_back(LoadTexture("Images/search.png"));
	icons.push_back(LoadTexture("Images/insert.png"));
	icons.push_back(LoadTexture("Images/delete.png"));
	icons.push_back(LoadTexture("Images/help.png"));
	icons.push_back(LoadTexture("Images/contact.png"));
	vector<Vector2> positions;
	positions.push_back({ iconPosX + (iconBoxWidth - iconSize) / 2, iconPosY + (iconBoxHeight - iconSize) / 2 });
	for (int i = 0; i < 4; i++) {
		positions.push_back({ positions.back().x + iconBoxWidth, positions.back().y });
	}
	vector<Vector2> boxPositions;
	boxPositions.push_back({ pageMarginLeft, pageMarginTop });
	for (int i = 0; i < 4; i++) {
		boxPositions.push_back({ boxPositions.back().x + iconBoxWidth, boxPositions.back().y });
	}
	//Search bar
	int searchBarWidth = 600;
	int searchBarHeight = 80;
	int searchBarFontSize = 40;
	double cursorTimer = 0.0f;
	bool showCursor = true;
	Rectangle searchBarBackground = { 0, toolBarBackground.height, screenWidth,  searchBarHeight + margin };
	Rectangle searchBarBoxPos = { (screenWidth - searchBarWidth) / 2, boxPositions[0].y + iconBoxHeight + margin, searchBarWidth, searchBarHeight };
	int searchCursorX = searchBarBoxPos.x + 10;
	int searchCursorY = searchBarBoxPos.y + (searchBarHeight - searchBarFontSize) / 2;
	//Suggestions
	//Hightlight when choosing, up and down when having suggestion, enter to choose, hightlightSuggestion < suggestions.size();
	int hightlightSuggestion = -1; //-1 for no hightlight
	int suggestionFontSize = 30;
	int suggestionMargin = 3;
	int suggestionBoxWidth = searchBarWidth;
	int suggestionBoxHeight = 50;
	vector<string> suggestions = { "got", "gotten", "Hello", "Gay" };

	//Result
	int resultMargin = 20;
	int resultWidth = 600;
	int resultHeight = 600;
	int resultStartPosX = pageMarginLeft;
	int resultStartPosY = searchBarBoxPos.y + searchBarHeight + margin;
	int keySize = 80;
	int meaningSize = keySize / 2;
	string key = "get";
	vector<string> meanings = { "nhan", "hieu", "biet" };

	while (true) {
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			//ctrl V 
			if (IsKeyPressed(KEY_V)) {
				const char* clipboardText = GetClipboardText();
				if (clipboardText != NULL) {
					key += clipboardText;
				}
			}
			//ctrl S
			else if (IsKeyPressed(KEY_S)) {
				mode = 0;
			}
			//ctrl I
			else if (IsKeyPressed(KEY_I)) {
				mode = 1;
			}
			//ctrl D
			else if (IsKeyPressed(KEY_D)) {
				mode = 2;
			}
			//ctrl H
			else if (IsKeyPressed(KEY_H)) {
				//Draw Help Page
			}
			//ctrl C
			else if (IsKeyPressed(KEY_C)) {
				//Draw Contact Page
			}
		}



		int input = GetKeyPressed();
		if (input != 0) cout << input << endl;
		if (input == KEY_BACKSPACE) {
			if (key.size() > 0) key.pop_back();
		}
		else if (input >= 'A' && input <= 'Z') {
			meanings.clear();
			key += input + 32;
			cout << key << endl;
		}
		else if (input == KEY_ENTER) {
			//Search
			if (mode == 0) {
				meanings.clear();
				//Search in dictionary
			}
			//Insert
			else if (mode == 1) {
				meanings.clear();
				//Insert to dictionary
			}
			//Delete
			else if (mode == 2) {
				meanings.clear();
				//Delete from dictionary
			}
			suggestions.clear();
		}

		//Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);

		//Draw Icons
		DrawRectangleRec(toolBarBackground, toolbarColor);
		for (int i = 0; i < icons.size(); i++) {
			DrawRectangle(boxPositions[i].x, boxPositions[i].y, iconBoxWidth, iconBoxHeight, WHITE);
			DrawRectangleLinesEx(Rectangle{ boxPositions[i].x, boxPositions[i].y, iconBoxWidth, iconBoxHeight }, borderThickness, BLACK);
			DrawTextureEx(icons[i], positions[i], 0, 1, WHITE);
		}

		//Draw Search Bar
		DrawRectangleRec(searchBarBackground, searchBarColor);
		DrawRectangleRec(searchBarBoxPos, WHITE);
		cursorTimer += GetFrameTime();
		if (cursorTimer >= 0.5f) {
			showCursor = !showCursor;
			cursorTimer = 0.0f;
		}
		DrawText(key.c_str(), searchBarBoxPos.x + 10, searchBarBoxPos.y + (searchBarHeight - searchBarFontSize) / 2, searchBarFontSize, BLACK);
		int textWidth = MeasureText(key.c_str(), searchBarFontSize);
		if (showCursor) DrawText("|", searchCursorX + textWidth, searchCursorY, 50, BLACK);

		//Draw Suggestions
		int i = 0;
		int suggestionPosY = searchBarBoxPos.y + searchBarHeight + suggestionMargin + (suggestionBoxHeight - suggestionFontSize) / 2;
		int suggestionBoxPosY = searchBarBoxPos.y + searchBarHeight + suggestionMargin;
		for (string& suggestion : suggestions) {
			if (i == hightlightSuggestion)
				DrawRectangle(searchBarBoxPos.x, suggestionBoxPosY, suggestionBoxWidth, suggestionBoxHeight, GRAY);
			else DrawRectangle(searchBarBoxPos.x, suggestionBoxPosY, suggestionBoxWidth, suggestionBoxHeight, WHITE);
			DrawText(suggestion.c_str(), searchBarBoxPos.x + 10, suggestionPosY, suggestionFontSize, BLACK);
			suggestionPosY += suggestionBoxHeight + suggestionMargin;
			suggestionBoxPosY += suggestionBoxHeight + suggestionMargin;
			i++;
		}
		//Draw Result
		int resultPosX = resultStartPosX;
		int resultPosY = resultStartPosY;
		DrawText(key.c_str(), resultPosX, resultPosY, keySize, BLACK);
		resultPosX += resultMargin;
		resultPosY += keySize;
		for (string& meaning : meanings) {
			resultPosY += meaningSize + resultMargin;
			DrawText(meaning.c_str(), resultPosX, resultPosY, meaningSize, BLACK);
		}

		EndDrawing();
	}

	for (auto& icon : icons)
		UnloadTexture(icon);
}