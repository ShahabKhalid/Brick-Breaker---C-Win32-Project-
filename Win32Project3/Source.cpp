/*-----------------------------------------------------------------------------------------------
									  Brick Breacker Turbo
									   By Shahab Khalid
									      ShabiSoft
									Copyright @ ShabiSoft
-------------------------------------------------------------------------------------------------


*************************************************************************************************
*************************************************************************************************
******************                     **************                        ********************
******************                     **************                        ********************
******************     ******************************      **************************************
******************     ******************************      **************************************
******************     ******************************      **************************************
******************                     **************                         *******************
******************                     **************                         *******************
**********************************     **********************************     *******************
**********************************     **********************************     *******************
**********************************     **********************************     *******************
*****************                      **************                         *******************
*****************                      **************                         *******************
*************************************************************************************************
*************************************************************************************************
*/






//================================================================================================
//										 INCLUDES
//================================================================================================
#include "res.h"




//================================================================================================
//										 wWinMain()
//================================================================================================
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Window Class";

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	
	wcex.style			= NULL;
	wcex.lpfnWndProc	= WindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wcex.hCursor		= LoadCursor(NULL, IDC_HAND);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= CLASS_NAME;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

	RegisterClassEx(&wcex);

	//global hInst to use out of WinMain
	g_hInst = hInstance; 


    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Brick Breaker | ShabiSoft",   // Window text
		WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        -8,-30, 1300, 795,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
        return 0;

	//Hiding Windows Border
	SetWindowLong(hwnd, GWL_STYLE, 0);

	//global win handle
	g_hwnd = hwnd;

	//Show Windows
    ShowWindow(hwnd, nCmdShow);
	

	//Load Level
	loadLevel("levels\\level1");

	//Threads
	pthread_create(&ballMovement, NULL, moveBall, NULL);

	//Getting msg from user for response
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

    return 0;
}





//================================================================================================
//                                   WindowProcedure
//================================================================================================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
	//Destroy Windows
    case WM_DESTROY:
        PostQuitMessage(0);
		break;

	//Windows Painting
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hmemdc,hdc = BeginPaint(hwnd, &ps);
			HPEN hpen;
			HBRUSH hbr;
			HFONT hfont;
			HGDIOBJ holdpen,holdbr,holdfont,holdbmp;
			LOGFONT f = {0};
			HBITMAP hbmp;
			//BackGround
			hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP6));
			
			hmemdc = CreateCompatibleDC(hdc);
			holdbmp = SelectObject(hmemdc,hbmp);

			BitBlt(hdc,0,0,1300,795,hmemdc,0,0,SRCCOPY);
			SelectObject(hmemdc,holdbmp);
			DeleteObject(hbmp);
			DeleteDC(hmemdc);


			LPCWSTR font = L"Arial"; 
			wcscpy(f.lfFaceName,font);
			f.lfHeight = 80;
			f.lfItalic = 1;



			switch(Menu)
			{

				
			//ShabiSoft Logo
			case 2:
				hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));

				hmemdc = CreateCompatibleDC(hdc);
				holdbmp = SelectObject(hmemdc,hbmp);

				BitBlt(hdc,0,0,1440,900,hmemdc,0,0,SRCCOPY);
				SelectObject(hmemdc,holdbmp);
				DeleteObject(hbmp);
				DeleteDC(hmemdc);
				Sleep(1000);
				

				keyNotice = 1;


				hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP2));

				if(keyNotice == 1) {
				hmemdc = CreateCompatibleDC(hdc);
				holdbmp = SelectObject(hmemdc,hbmp);

				BitBlt(hdc,210,500,1010,700,hmemdc,0,0,SRCCOPY);
				SelectObject(hmemdc,holdbmp);
				DeleteObject(hbmp);
				DeleteDC(hmemdc);
				keyNotice = 2;}
				else if(keyNotice == 2)
					keyNotice == 1;
				Sleep(1000);
				
			
				break;


			//Main Menu
			case 0: {


				hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP3));

				hmemdc = CreateCompatibleDC(hdc);
				holdbmp = SelectObject(hmemdc,hbmp);

				BitBlt(hdc,0,0,1440,900,hmemdc,0,0,SRCCOPY);
				SelectObject(hmemdc,holdbmp);
				DeleteObject(hbmp);
				DeleteDC(hmemdc);


				hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP4));

				hmemdc = CreateCompatibleDC(hdc);
				holdbmp = SelectObject(hmemdc,hbmp);

				BitBlt(hdc,menuSpos[0],menuSpos[1],menuSpos[0]+148,menuSpos[2]+100,hmemdc,0,0,SRCCOPY);
				SelectObject(hmemdc,holdbmp);
				DeleteObject(hbmp);
				DeleteDC(hmemdc);

				break;
				}

			//Game Screen
			case 1: {

			if(!GameOver) {



			for(int i = 0;i < cBricks;i++)
				if(bricks[i].show)
				{
					if(bricks[i].type == NORMBRICK)
					{
						hbr = CreateSolidBrush(RGB(200,200,0));
						holdbr = SelectObject(hdc,hbr);
					}
					else if(bricks[i].type == SOLIDBRICK)
					{
						hbr = CreateSolidBrush(RGB(155,155,0));
						holdbr = SelectObject(hdc,hbr);
					}
					else if(bricks[i].type == EXSOLIDBRICK)
					{
						hbr = CreateSolidBrush(RGB(98,95,90));
						holdbr = SelectObject(hdc,hbr);
					}

					Rectangle(hdc,bricks[i].left,bricks[i].top,bricks[i].right,bricks[i].bottom);
					SelectObject(hdc,holdbr);
					DeleteObject(hbr);
				}


			f.lfHeight = 300;
			hfont = CreateFontIndirect(&f);
			holdfont = SelectObject(hdc, hfont);
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(175, 175, 175));
			wchar_t scoretxt[3];
			swprintf(scoretxt, L"%d", score);
			TextOut(hdc, 500, 300, scoretxt, wcslen(scoretxt));


			f.lfHeight = 15;

			hfont = CreateFontIndirect(&f);
			holdfont = SelectObject(hdc,hfont);
			SetBkMode(hdc,TRANSPARENT);
			SetTextColor(hdc,RGB(175,0,0));
			if (brickMag) TextOut(hdc, 500, 770, L"Magnet", 6);
			if(brickSpeed == 30)TextOut(hdc,600,770,L"Speedy Brick",12);
			if(brickSpeed == 10)TextOut(hdc,700,770,L"Slow Brick",10);
			if(bSpeed == 10)TextOut(hdc,800,770,L"Speedy Ball",11);
			if(brick.hide)TextOut(hdc,900,770,L"Trasparent Brick",16);


			


			
				

			SetTextColor(hdc,RGB(255,255,255));
			switch(bonus[0])
			{
				case 1: {
					TextOut(hdc,bonus[1],bonus[2],L"T",1);
				break; }
				case 2: {
					TextOut(hdc,bonus[1],bonus[2],L"S",1);
				break; }
				case 3: {
					TextOut(hdc,bonus[1],bonus[2],L"F",1);
				break; }
				case 4: {
					TextOut(hdc,bonus[1],bonus[2],L"BF",1);
				break; }
				case 5: {
					TextOut(hdc,bonus[1],bonus[2],L"M",1);
				break; }
				case 6: {
					TextOut(hdc,bonus[1],bonus[2],L"N",1);
				break; }
			}

			SelectObject(hdc,holdfont);
			DeleteObject(hfont);


			hbr = CreateSolidBrush(RGB(150,0,0));
			holdbr = SelectObject(hdc,hbr);
			Ellipse(hdc,ball.left,ball.top,ball.right,ball.bottom);
			SelectObject(hdc,holdbr);
			DeleteObject(hbr);

			if(!brick.hide) hpen = CreatePen(PS_SOLID,10,RGB(125,0,0));
			else hpen = CreatePen(PS_SOLID,10,RGB(0,0,0));
			holdpen = SelectObject(hdc,hpen);

			MoveToEx(hdc,brick.startX,brick.startY,NULL);
			LineTo(hdc,brick.endX,brick.endY);

			SelectObject(hdc,holdpen);
			DeleteObject(hpen);

			}
			else {
				hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP5));

				hmemdc = CreateCompatibleDC(hdc);
				holdbmp = SelectObject(hmemdc,hbmp);

				BitBlt(hdc,0,0,1440,900,hmemdc,0,0,SRCCOPY);
				SelectObject(hmemdc,holdbmp);
				DeleteObject(hbmp);
				DeleteDC(hmemdc);
			}



			break;}

			}



			EndPaint(hwnd, &ps);
			break;
        }

	//OnKeyDown()
	case WM_KEYDOWN:
		{
			if(keyNotice == 1 || keyNotice == 2) {
				keyNotice = 0;
				Menu = 0;
				InvalidateRect(g_hwnd, 0, TRUE);
			}
			switch(wParam)
			{
				case VK_RIGHT:
				{
					if(Menu == 1) 
						moveBrick("right"); 
					break;
				}
				case VK_LEFT:
				{
					if(Menu == 1)
						moveBrick("left");
					break;
				}
				case VK_UP:
				{
					if(Menu == 0) {
						switch(menuSelect)
						{
							case 0:{
								menuSelect = 2;
								menuSpos[1] = 550;
								break; }
							case 1:{
								menuSelect = 0;
								menuSpos[1] -= 100;
								break; }
							case 2:{
								menuSelect = 1;
								menuSpos[1] -= 100;
								break; }
						}
					}
					else if(Menu == 1)
						Start = true;

					InvalidateRect(g_hwnd, 0, TRUE);
					break;
				}
				case VK_DOWN:
				{
					if(Menu == 0) {
						switch(menuSelect)
						{
							case 0:{
								menuSelect = 1;
								menuSpos[1] += 100;
								break; }
							case 1:{
								menuSelect = 2;
								menuSpos[1] += 100;
								break; }
							case 2:{
								menuSelect = 0;
								menuSpos[1] = 350;
								break; }
						}
						
					}
					InvalidateRect(g_hwnd, 0, TRUE);
					break;
				}
				case VK_TAB:
				{
					bricks[del++].show = false;
					InvalidateRect(g_hwnd, 0, TRUE);
					break;
				}
				case VK_RETURN:
				{
					switch(Menu)
					{

					//Main Menu
					case 0: {
					switch(menuSelect)
					{
						//Start Game
						case 0:{
							Menu = 1;
							score = 0;
							InvalidateRect(g_hwnd, 0, TRUE);
							break;
								}

							//About Us
							case 1: {
								MessageBox(hwnd,L"Brick Breaker\nCopyright 2013 @ ShabiSoft\nCIIT, ICP Project",L"About Us",0);
							break;}

							case 2: {
								PostQuitMessage(0);
							break;}
					}
					break;}

					//Game Screen
					case 1: {
						changeLevel("levels\\level1");
						Start = false;
						GameOver = false;
						Menu = 0;
						bonus[0] = 0;
						InvalidateRect(g_hwnd, 0, TRUE);
					break;}



					}
				}
					
			}
		}
        return 0;

    }
	//else default actions
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}




//================================================================================================
//								        moveBrick
//================================================================================================
void moveBrick(char dir[])
{
	if(!strcmp(dir,"right"))			
		if(brick.endX <= 950)
		{
			if(!Start) {
				ball.left += brickSpeed;
				ball.right += brickSpeed;
				InvalidateRect(g_hwnd, 0, TRUE);}
			brick.startX += brickSpeed;
			brick.endX += brickSpeed;
		}

	if(!strcmp(dir,"left"))			
		if(brick.startX >= 350)
		{
				if(!Start) {
				ball.left -= brickSpeed;
				ball.right -= brickSpeed;
				InvalidateRect(g_hwnd, 0, TRUE);}
			brick.startX -= brickSpeed;
			brick.endX -= brickSpeed;
		}
}


//================================================================================================
//								        moveBall
//================================================================================================
void * moveBall(void * args)
{
	while(1)
	{	
		if(Start) {
			if(ball.bottom > brick.endY+5) {
				GameOver = true;
				InvalidateRect(g_hwnd,0,true);
				Start = false;
			}

			if(bCollideWithpBrick())
					strcpy_s(ballDir,"up");

			//Top Collision
			if(!strcmp(ballDir,"up")) 
			{
				if(ball.top <= 0)
				{
					strcpy_s(ballDir,"down");
				}
				if (bAngle > 3 && bAngle <= 5) spcontler = 1;
				else if (bAngle > 5) spcontler = 2;
				else spcontler = 0;
				ball.top -= bSpeed - spcontler;
				ball.bottom -= bSpeed - spcontler;
			}
			else if(!strcmp(ballDir,"down")) 
			{
				if (bAngle > 3 && bAngle <= 5) spcontler = 1;
				else if (bAngle > 5) spcontler = 2;
				else spcontler = 0;
				ball.top += bSpeed - spcontler;
				ball.bottom += bSpeed - spcontler;
			}

			//Angle Movement
			ball.left += bAngle;
			ball.right += bAngle;

			//Collision with walls
			bCollideWithSideWalls();


			//Collision With bricks
			bCollideWithBricks();
			


			//Bonus Mover
			if(bonus[0])
			{
			

			if(bonus[1] >= brick.startX && bonus[1] <= brick.endX) {
				if(bonus[2] >= brick.startY-3 && bonus[2] <= brick.endY+3) 
				{
					switch(bonus[0])
					{
					case 1: {
						brick.hide = true;
						break;
						}
					case 2: {
						brickSpeed = 10;
						break;
						}
					case 3: {
						brickSpeed = 30;
						break;
						}
					case 4: {
						bSpeed = 20;
						break;
						}
					case 5: {
						brickMag = true;
						break;
						}
					case 6: {
						brickMag = false;
						bSpeed = 2;
						brickSpeed = 20;
						brick.hide = false;
						break;
						}
					}
					bonus[0] = 0;
				} }
			
			bonus[2]++;
			if(bonus[2] >= brick.startY+5) bonus[0] = 0;
			}


			//Level Changing
					for(int i = 0;i < cBricks;i++)
			if(bricks[i].show)
				countbShows++;

		if(countbShows == 0) {
			switch(level)
			{
				case 0: {
				changeLevel("levels\\level2");
				level = 1;
				break; }
				case 1: {
				changeLevel("levels\\level3");
				level = 2;
				break;}
				case 2: {
				changeLevel("levels\\level4");
				level = 3;
				break; }
				case 3: {
				changeLevel("levels\\level5");
				level = 4;
				break; }
				case 4: {
				Menu = 0;
				Start = 0;
				changeLevel("levels\\level1");
				level = 0;
				break; }
				del = 0;
			}
			bSpeed += 2;
			ball.left = 620;
			ball.top = 765;
			ball.right = 630;
			ball.bottom = 775;
			brick.startX = 600;
			brick.startY = 780;
			brick.endX = 650;
			brick.endY = 780;
			Start = false;
		}
		countbShows = 0;
		}

		if(Start || keyNotice != 0) { 
		InvalidateRect(g_hwnd, 0, TRUE);
		Sleep(10); }
	}
	return (void *) 1;
}




//================================================================================================
//								        bCollideWithpBrick
//================================================================================================
bool bCollideWithpBrick()
{
	if(!strcmp(ballDir,"down")) 
	{
		if(ball.left > brick.startX-20 && ball.right < brick.endX+20)
			if(ball.bottom >= brick.startY) {
				ball.bottom += 2;
				ball.top += 2;
				bAngle += (((ball.left + ball.right) / 2) - ((brick.startX + brick.endX) / 2)) / 10;
				if(brickMag) {
					Start = 0;
					bAngle = 0;
					ball.top = 770;
					ball.bottom = 780;}
				return true; }
	}
	return false;
}






//================================================================================================
//								        bCollideWithBricks
//================================================================================================
void bCollideWithBricks()
{
	bool hitsCheck = false;
	if(!strcmp(ballDir,"up")) 
	{
		for(int i = 0; i < cBricks;i++) 
			if(bricks[i].show)
				if(ball.left > bricks[i].left-20 && ball.right < bricks[i].right+20)
					if(ball.top <= bricks[i].bottom && ball.top >= bricks[i].bottom-10) {
						bAngle += (((ball.left + ball.right) / 2) - ((bricks[i].left + bricks[i].right) / 2)) / 10;
						strcpy_s(ballDir,"down");
						bricks[i].hits++;
						switch(bricks[i].type)
						{
							case NORMBRICK: {
								if(bricks[i].hits >= 1)	
									hitsCheck = true;
							}
							case SOLIDBRICK: {
								if(bricks[i].hits >= 3)	
									hitsCheck = true;
							}
							case EXSOLIDBRICK: {
								if(bricks[i].hits >= 5)	
									hitsCheck = true;
							}

						}

						if(hitsCheck) {
							int rand = getrand(100,1000);

							if(rand >= 100 && rand < 130) {
									if(bonus[0] == 0)	bonus[0] = 1;//Transparent
								}
							else if(rand >= 200 && rand < 220) {
									if(bonus[0] == 0)	bonus[0] = 2;//Slow Brick
								}
							else if(rand >= 320 && rand < 330) {
									if(bonus[0] == 0)	bonus[0] = 3;//Fast Brick
								}
							else if(rand >= 430 && rand < 440) {
									if(bonus[0] == 0)	bonus[0] = 4;//fast Ball
								}
							else if(rand >= 440 && rand < 680) {
									if(bonus[0] == 0)	bonus[0] = 5;//Magnet
								}
							else if(rand >= 680 && rand < 800) {
									if(bonus[0] == 0)	bonus[0] = 6;//Normal
								}
						if(bonus[0] == 0) {
						bonus[1] = bricks[i].right;
						bonus[2] = bricks[i].bottom; }
						bricks[i].show = false;
						score++;
						hitsCheck = false;}
					}
	}
	if(!strcmp(ballDir,"down")) 
	{
		for(int i = 0; i < cBricks;i++)
			if(bricks[i].show)
				if(ball.left > bricks[i].left-20 && ball.right < bricks[i].right+20)
					if(ball.bottom >= bricks[i].top && ball.bottom <= bricks[i].top+10) {
						bAngle += (((ball.left + ball.right) / 2) - ((bricks[i].left + bricks[i].right) / 2)) / 10;
						strcpy_s(ballDir,"up");
						bricks[i].hits++;

						switch(bricks[i].type)
						{
							case NORMBRICK: {
								if(bricks[i].hits >= 1)	
									hitsCheck = true;
							}
							case SOLIDBRICK: {
								if(bricks[i].hits >= 3)	
									hitsCheck = true;
							}
							case EXSOLIDBRICK: {
								if(bricks[i].hits >= 5)	
									hitsCheck = true;
							}

						}

						if(hitsCheck) {
							int rand = getrand(100,1000);

							if(rand >= 100 && rand < 130) {
									if(bonus[0] == 0)	bonus[0] = 1;//Transparent
								}
							else if(rand >= 200 && rand < 220) {
									if(bonus[0] == 0)	bonus[0] = 2;//Slow Brick
								}
							else if(rand >= 320 && rand < 330) {
									if(bonus[0] == 0)	bonus[0] = 3;//Fast Brick
								}
							else if(rand >= 430 && rand < 440) {
									if(bonus[0] == 0)	bonus[0] = 4;//Fast Ball
								}
							else if(rand >= 440 && rand < 480) {
									if(bonus[0] == 0)	bonus[0] = 5;//Magnet
								}
							else if(rand >= 480 && rand < 500) {
									if(bonus[0] == 0)	bonus[0] = 6;//Normal
								}
						
						if(bonus[0] == 0) {
						bonus[1] = bricks[i].right;
						bonus[2] = bricks[i].bottom; }
						bricks[i].show = false;
						score++;
						hitsCheck = false;}
		}
	}
}




//================================================================================================
//								     bCollideWithSideWalls
//================================================================================================
void bCollideWithSideWalls()
{
	if(ball.left <= 350 || ball.right >= 950)
	{
		bAngle = -bAngle;
	}
}





//================================================================================================
//								        resetLevel
//================================================================================================
void resetLevel()
{
	for(int i = 0;i < cBricks;i++)
		bricks[i].show = true;

	ball.left = 620;
	ball.top = 765;
	ball.right = 630;
	ball.bottom = 775;
	brick.startX = 600;
	brick.startY = 780;
	brick.endX = 650;
	brick.endY = 780;
	bAngle = 0;
	brickMag = false;
	bSpeed = 2;
	brickSpeed = 20;
	brick.hide = false;
}






//================================================================================================
//								        loadLevel
//================================================================================================
bool loadLevel(char map[])
{
	FILE *f;
	char str[80];
	int i = 0;
	f = fopen(map,"r");
	if(f == NULL) {
		return false; }

	while(fgets(str,79,f) != NULL) {
		b_fscanf(str,bricks[i]);
		bricks[i++].show = true; 
		cBricks++;}

	fclose(f);
	return true;
}





//================================================================================================
//								        changeLevel
//================================================================================================
bool changeLevel(char map[])
{
	resetLevel();
	if(loadLevel(map))
		return true;
	return false;
}




//================================================================================================
//								        b_fscanf
//================================================================================================
void b_fscanf(char str[],sBricks &bk)
{
	int start = 0,end = 0,i,j,k = 0,counter = 0;
	char tmpstr[10];
	puts(str);
	for(i = 0;i <= strlen(str);i++)
	{
		if(str[i] == '|' || str[i] == '\0')
		{
			end = i;
			for(j = start;j < end;j++)
			{
				tmpstr[k++] = str[j];
			}
			tmpstr[k] = '\0';
			puts(tmpstr);
			switch(counter)
			{
				case 0:
				{
					bk.left = (int)atol(tmpstr);
					break;
				}
				case 1:
				{
					bk.top = (int)atol(tmpstr);
					break;
				}
				case 2:
				{
					bk.right = (int)atol(tmpstr);
					break;
				}
				case 3:
				{
					bk.bottom = (int)atol(tmpstr);
					break;
				}
				case 4:
				{
					bk.type = (int)atol(tmpstr);
					break;
				}
			}
			counter++;
			start = end + 1;
			k = 0;
			strcpy_s(tmpstr,"");
		}
	}
}

