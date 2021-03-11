#include "engine.h"
extern draw drawing;
extern input gameinput;
extern engine gameengine;
extern debug debugger;
const int BLANK		=0;
const int FUNGUS	=1;
const int BRICK		=2;
const int PLAYER	=3;
const int GRASS		=4;
const int BOULDER	=5;
const int DIAMOND	=6;
const int FIRE		=7;
void blankcall(bool pressed) {
	if (pressed) 
		gameengine.tool=0;
}
void funguscall(bool pressed) {
	if (pressed) 
		gameengine.tool=1;
}
void engine::SaveState(void) {
	diamondcount=0;
	if (backup) {
		for (int temp=0;temp<width;temp++)
			delete [] backup[temp];
		delete [] backup;
	}
	backup = new char*[width];
	for (int temp=0;temp<width;temp++)
		backup[temp] = new char[height];
	for (temp=0;temp<width;temp++)
		for (int temp2=0;temp2<height;temp2++)
			backup[temp][temp2]=field[temp][temp2];

}
void engine::LoadState(void) {
	diamondcount=0;
	for (int temp=0;temp<width;temp++)
		for (int temp2=0;temp2<height;temp2++)
			field[temp][temp2]=backup[temp][temp2];
}
void runcall(bool pressed) {
	if (pressed) {
		if (state==1) {
			gameengine.SaveState();
			state=2;
		}
		else {
			gameengine.LoadState();
			state=1;
		}
	}
}
void brickcall(bool pressed) {
	if (pressed) 
		gameengine.tool=2;
}
void playercall(bool pressed) {
	if (pressed) 
		gameengine.tool=3;
}

void grasscall(bool pressed) {
	if (pressed) 
		gameengine.tool=4;
}
void bouldercall(bool pressed) {
	if (pressed) 
		gameengine.tool=5;
}
void diamondcall(bool pressed) {
	if (pressed) 
		gameengine.tool=6;
}
void firecall(bool pressed) {
	if (pressed) 
		gameengine.tool=7;
}
void savecall(void) {
	gameengine.save.GiveMessage(CONTROL_ACTIVATE,0,0);
}
void loadcall(void) {
	gameengine.load.GiveMessage(CONTROL_ACTIVATE,0,0);
}
engine::engine(void) {
	changed=true;
	toolswindow.GiveMessage(CONTROL_SETPOS,0,0);
	toolswindow.GiveMessage(CONTROL_SETSIZE,70,200);
	blanktool.GiveMessage(CONTROL_SETPOS,1,21);
	blanktool.GiveMessage(CONTROL_SETSIZE,32,32);
	blanktool.GiveMessage(CBUTTON_SOLID,1,0);
	blanktool.GiveMessage(CBUTTON_SETCALLBACK,(int)blankcall,0);
	fungustool.GiveMessage(CONTROL_SETPOS,33,21);
	fungustool.GiveMessage(CONTROL_SETSIZE,32,32);
	fungustool.GiveMessage(CBUTTON_SOLID,1,0);
	fungustool.GiveMessage(CBUTTON_SETCALLBACK,(int)funguscall,0);
	bricktool.GiveMessage(CONTROL_SETPOS,1,53);
	bricktool.GiveMessage(CONTROL_SETSIZE,32,32);
	bricktool.GiveMessage(CBUTTON_SOLID,1,0);
	bricktool.GiveMessage(CBUTTON_SETCALLBACK,(int)brickcall,0);
	playertool.GiveMessage(CONTROL_SETPOS,33,53);
	playertool.GiveMessage(CONTROL_SETSIZE,32,32);
	playertool.GiveMessage(CBUTTON_SOLID,1,0);
	playertool.GiveMessage(CBUTTON_SETCALLBACK,(int)playercall,0);
	grasstool.GiveMessage(CONTROL_SETPOS,1,85);
	grasstool.GiveMessage(CONTROL_SETSIZE,32,32);
	grasstool.GiveMessage(CBUTTON_SOLID,1,0);
	grasstool.GiveMessage(CBUTTON_SETCALLBACK,(int)grasscall,0);
	bouldertool.GiveMessage(CONTROL_SETPOS,33,85);
	bouldertool.GiveMessage(CONTROL_SETSIZE,32,32);
	bouldertool.GiveMessage(CBUTTON_SOLID,1,0);
	bouldertool.GiveMessage(CBUTTON_SETCALLBACK,(int)bouldercall,0);
	diamondtool.GiveMessage(CONTROL_SETPOS,1,117);
	diamondtool.GiveMessage(CONTROL_SETSIZE,32,32);
	diamondtool.GiveMessage(CBUTTON_SOLID,1,0);
	diamondtool.GiveMessage(CBUTTON_SETCALLBACK,(int)diamondcall,0);
	firetool.GiveMessage(CONTROL_SETPOS,33,117);
	firetool.GiveMessage(CONTROL_SETSIZE,32,32);
	firetool.GiveMessage(CBUTTON_SOLID,1,0);
	firetool.GiveMessage(CBUTTON_SETCALLBACK,(int)firecall,0);
	toolswindow.AddChild(&playertool);
	toolswindow.AddChild(&bricktool);
	toolswindow.AddChild(&blanktool);
	toolswindow.AddChild(&fungustool);
	toolswindow.AddChild(&grasstool);
	toolswindow.AddChild(&bouldertool);
	toolswindow.AddChild(&diamondtool);
	toolswindow.AddChild(&firetool);
	runbutton.GiveMessage(CONTROL_SETPOS,width/2-16,height-32);
	runbutton.GiveMessage(CONTROL_SETSIZE,32,32);
	runbutton.GiveMessage(CBUTTON_SOLID,1,0);
	runbutton.GiveMessage(CBUTTON_SETCALLBACK,(int)runcall,0);
	tool=0;
	save.GiveMessage(CONTROL_SETPOS,0,0);
	save.GiveMessage(CONTROL_SETSIZE,200,200);
	load.GiveMessage(CONTROL_SETPOS,0,0);
	load.GiveMessage(CONTROL_SETSIZE,200,200);
	save.GiveMessage(CWINDOW_TOGGLECLOSEBUTTON,1,0);
	load.GiveMessage(CWINDOW_TOGGLECLOSEBUTTON,1,0);
	save.GiveMessage(CWINDOW_SETCLOSECALLBACK,(int)savecall,0);
	load.GiveMessage(CWINDOW_SETCLOSECALLBACK,(int)loadcall,0);
	save.AddChild(&saveedit);
	load.AddChild(&loadedit);
	save.AddChild(&savetext);
	load.AddChild(&loadtext);
	savetext.GiveMessage(CONTROL_SETPOS,1,21);
	loadtext.GiveMessage(CONTROL_SETPOS,1,21);
	savetext.GiveMessage(CTEXT_SETTEXT,(int)"Input filename to save:",0);
	loadtext.GiveMessage(CTEXT_SETTEXT,(int)"Input filename to load:",0);
	save.GiveMessage(CONTROL_ACTIVATE,0,0);
	load.GiveMessage(CONTROL_ACTIVATE,0,0);
	savetext.GiveMessage(CTEXT_SETCOLOR,RGB(192,192,192),0);
	loadtext.GiveMessage(CTEXT_SETCOLOR,RGB(192,192,192),0);
	saveedit.GiveMessage(CONTROL_SETPOS,1,33);
	saveedit.GiveMessage(CONTROL_SETSIZE,198,166);
	saveedit.GiveMessage(CEDIT_SETCALLBACK,(int)SaveMap,0);
	loadedit.GiveMessage(CONTROL_SETPOS,1,33);
	loadedit.GiveMessage(CONTROL_SETSIZE,198,166);
	loadedit.GiveMessage(CEDIT_SETCALLBACK,(int)LoadMap,0);
	saveedit.GiveMessage(CEDIT_SETBGCOLOR,RGB(0,0,0),0);
	saveedit.GiveMessage(CEDIT_SETTOPLEFTCOLOR,RGB(192,192,192),0);
	saveedit.GiveMessage(CEDIT_SETBOTTOMRIGHTCOLOR,RGB(92,92,92),0);
	saveedit.GiveMessage(CEDIT_SETCARETCOLOR,RGB(128,128,128),0);
	saveedit.GiveMessage(CEDIT_SETTEXTCOLOR,RGB(192,192,192),0);
	loadedit.GiveMessage(CEDIT_SETBGCOLOR,RGB(0,0,0),0);
	loadedit.GiveMessage(CEDIT_SETTOPLEFTCOLOR,RGB(192,192,192),0);
	loadedit.GiveMessage(CEDIT_SETBOTTOMRIGHTCOLOR,RGB(92,92,92),0);
	loadedit.GiveMessage(CEDIT_SETCARETCOLOR,RGB(128,128,128),0);
	loadedit.GiveMessage(CEDIT_SETTEXTCOLOR,RGB(192,192,192),0);
}
void engine::initialize(int target2) {
	target=target2;
	blanktool.	GiveMessage	(CBUTTON_SETUP	,drawing.LoadSurface("blankup.bmp")		,0);
	blanktool.	GiveMessage	(CBUTTON_SETDOWN,drawing.LoadSurface("blankdown.bmp")	,0);
	fungustool.	GiveMessage	(CBUTTON_SETUP	,drawing.LoadSurface("fungusup.bmp")	,0);
	fungustool.	GiveMessage	(CBUTTON_SETDOWN,drawing.LoadSurface("fungusdown.bmp")	,0);
	runbutton.	GiveMessage	(CBUTTON_SETUP	,drawing.LoadSurface("runup.bmp")		,0);
	runbutton.	GiveMessage	(CBUTTON_SETDOWN,drawing.LoadSurface("rundown.bmp")		,0);
	bricktool.	GiveMessage	(CBUTTON_SETUP	,drawing.LoadSurface("brickup.bmp")		,0);
	bricktool.	GiveMessage	(CBUTTON_SETDOWN,drawing.LoadSurface("brickdown.bmp")	,0);
	playertool.	GiveMessage	(CBUTTON_SETUP	,drawing.LoadSurface("playerup.bmp")	,0);
	playertool.	GiveMessage	(CBUTTON_SETDOWN,drawing.LoadSurface("playerdown.bmp")	,0);
	grasstool.	GiveMessage	(CBUTTON_SETUP	,drawing.LoadSurface("grassup.bmp")		,0);
	grasstool.	GiveMessage	(CBUTTON_SETDOWN,drawing.LoadSurface("grassdown.bmp")	,0);
	bouldertool.GiveMessage	(CBUTTON_SETUP	,drawing.LoadSurface("boulderup.bmp")	,0);
	bouldertool.GiveMessage	(CBUTTON_SETDOWN,drawing.LoadSurface("boulderdown.bmp")	,0);
	diamondtool.GiveMessage	(CBUTTON_SETUP	,drawing.LoadSurface("diamondup.bmp")	,0);
	diamondtool.GiveMessage	(CBUTTON_SETDOWN,drawing.LoadSurface("diamonddown.bmp")	,0);
	firetool.	GiveMessage	(CBUTTON_SETUP	,drawing.LoadSurface("fireup.bmp")		,0);
	firetool.	GiveMessage	(CBUTTON_SETDOWN,drawing.LoadSurface("firedown.bmp")	,0);
	save.		GiveMessage	(CWINDOW_SETCLOSEPICTURES,drawing.LoadSurface("close.bmp"),drawing.LoadSurface("closedown.bmp"));
	load.		GiveMessage	(CWINDOW_SETCLOSEPICTURES,drawing.LoadSurface("close.bmp"),drawing.LoadSurface("closedown.bmp"));
}
bool checkfield(int x,int y,deque<int> *xcheck,deque<int> *ycheck) {
	bool ret=true;
	for (int temp=0;temp<xcheck->size();temp++)
		if (xcheck->operator[](temp)==x&&ycheck->operator[](temp)==y) {
			ret=false;
			break;
		}
	return ret;
}
void engine::ProcessField(void) {
	deque<int> xcheck;
	deque<int> ycheck;
	for (int temp=0;temp<width;temp++)
		for (int temp2=0;temp2<height;temp2++)
			if (checkfield(temp,temp2,&xcheck,&ycheck))
			switch (field[temp][temp2]) {
			case BLANK:
				break;
			case FUNGUS:
				if (temp&&field[temp-1][temp2]==BLANK) {
					field[temp-1][temp2]=1;
					xcheck.push_back(temp-1);
					ycheck.push_back(temp2);
				}
				if (temp<width-1&&field[temp+1][temp2]==BLANK) {
					field[temp+1][temp2]=1;
					xcheck.push_back(temp+1);
					ycheck.push_back(temp2);
				}
				if (temp2&&field[temp][temp2-1]==BLANK) {
					field[temp][temp2-1]=1;
					xcheck.push_back(temp);
					ycheck.push_back(temp2-1);
				}
				if (temp<height-1&&field[temp][temp2+1]==BLANK) {
					field[temp][temp2+1]=1;
					xcheck.push_back(temp);
					ycheck.push_back(temp2+1);
				}
				break;
			case BRICK:
				break;
			case PLAYER:
				if (temp&&gameinput.KeyPressed(DIK_LEFT)) {
					if (field[temp-1][temp2]==BLANK||field[temp-1][temp2]==GRASS) {
						field[temp-1][temp2]=3;
						field[temp][temp2]=0;
						xcheck.push_back(temp-1);
						ycheck.push_back(temp2);
					} else if (temp>1&&field[temp-2][temp2]==BLANK&&field[temp-1][temp2]==BOULDER) {
						field[temp-2][temp2]=BOULDER;
						field[temp-1][temp2]=PLAYER;
						field[temp][temp2]=BLANK;
					} else if (temp && field[temp-1][temp2]==DIAMOND) {
						diamondcount++;
						field[temp-1][temp2]=PLAYER;
						field[temp][temp2]=BLANK;
						xcheck.push_back(temp-1);
						ycheck.push_back(temp2);
					}
				} else if (temp<width-1&&gameinput.KeyPressed(DIK_RIGHT)) {
					if (field[temp+1][temp2]==BLANK||field[temp+1][temp2]==GRASS) {
						field[temp+1][temp2]=3;
						field[temp][temp2]=0;
						xcheck.push_back(temp+1);
						ycheck.push_back(temp2);
					} else if (temp<width-2&&field[temp+2][temp2]==BLANK&&field[temp+1][temp2]==BOULDER) {
						field[temp+2][temp2]=BOULDER;
						field[temp+1][temp2]=PLAYER;
						field[temp][temp2]=BLANK;
						xcheck.push_back(temp+2);
						ycheck.push_back(temp2);
						xcheck.push_back(temp+1);
						ycheck.push_back(temp2);
					} else if (temp<width-1 && field[temp+1][temp2]==DIAMOND) {
						diamondcount++;
						field[temp+1][temp2]=PLAYER;
						field[temp][temp2]=BLANK;
						xcheck.push_back(temp+1);
						ycheck.push_back(temp2);
					}
				} else if (temp2&&gameinput.KeyPressed(DIK_UP)) {
					if (field[temp][temp2-1]==BLANK||field[temp][temp2-1]==GRASS) {
						field[temp][temp2-1]=3;
						field[temp][temp2]=0;
						xcheck.push_back(temp);
						ycheck.push_back(temp2-1);
					} else if (temp2&&field[temp][temp2-1]==DIAMOND) {
						diamondcount++;
						field[temp][temp2-1]=PLAYER;
						field[temp][temp2]=BLANK;
						xcheck.push_back(temp);
						ycheck.push_back(temp2-1);
					}
				} else if (temp2<height-1&&gameinput.KeyPressed(DIK_DOWN)) {
					if (field[temp][temp2+1]==BLANK||field[temp][temp2+1]==GRASS) {
						field[temp][temp2+1]=3;
						field[temp][temp2]=0;
						xcheck.push_back(temp);
						ycheck.push_back(temp2+1);
					} else if (temp2&&field[temp][temp2+1]==DIAMOND) {
						diamondcount++;
						field[temp][temp2+1]=PLAYER;
						field[temp][temp2]=BLANK;
						xcheck.push_back(temp);
						ycheck.push_back(temp2+1);
					}
				}
				break;
			case GRASS:
				break;
			case BOULDER:
				if (temp2<height-1&&field[temp][temp2+1]==BLANK) {
					field[temp][temp2]=BLANK;
					field[temp][temp2+1]=BOULDER;
					xcheck.push_back(temp);
					ycheck.push_back(temp2+1);
				} else if (temp&&temp2<height-1&&field[temp-1][temp2]==BLANK&&field[temp-1][temp2+1]==BLANK) {
					field[temp][temp2]=0;
					field[temp-1][temp2+1]=BOULDER;
					xcheck.push_back(temp-1);
					ycheck.push_back(temp2+1);
				} else if (temp<width-1&&temp2<height-1&&field[temp+1][temp2]==BLANK&&field[temp+1][temp2+1]==BLANK) {
					field[temp][temp2]=0;
					field[temp+1][temp2+1]=BOULDER;
					xcheck.push_back(temp+1);
					ycheck.push_back(temp2+1);
				}
				break;
			case DIAMOND:
				if (temp2<height-1&&field[temp][temp2+1]==BLANK) {
					field[temp][temp2]=BLANK;
					field[temp][temp2+1]=DIAMOND;
					xcheck.push_back(temp);
					ycheck.push_back(temp2+1);
				} else if (temp&&temp2<height-1&&field[temp-1][temp2]==BLANK&&field[temp-1][temp2+1]==BLANK) {
					field[temp][temp2]=0;
					field[temp-1][temp2+1]=DIAMOND;
					xcheck.push_back(temp-1);
					ycheck.push_back(temp2+1);
				} else if (temp<width-1&&temp2<height-1&&field[temp+1][temp2]==BLANK&&field[temp+1][temp2+1]==BLANK) {
					field[temp][temp2]=0;
					field[temp+1][temp2+1]=DIAMOND;
					xcheck.push_back(temp+1);
					ycheck.push_back(temp2+1);
				}
				break;
			case FIRE:
				{
					bool found = false;
					if (temp&&(field[temp-1][temp2]==FUNGUS||field[temp-1][temp2]==GRASS)) {
						field[temp-1][temp2]=FIRE;
						xcheck.push_back(temp-1);
						ycheck.push_back(temp2);
					}
					if (temp<width-1&&(field[temp+1][temp2]==FUNGUS||field[temp+1][temp2]==GRASS)) {
						field[temp+1][temp2]=FIRE;
						xcheck.push_back(temp+1);
						ycheck.push_back(temp2);
					}
					if (temp2&&(field[temp][temp2-1]==FUNGUS||field[temp][temp2-1]==GRASS)) {
						field[temp][temp2-1]=FIRE;
						xcheck.push_back(temp);
						ycheck.push_back(temp2-1);
					}
					if (temp2<height-1&&(field[temp][temp2+1]==FUNGUS||field[temp][temp2+1]==GRASS) ) {
						field[temp][temp2+1]=FIRE;
						xcheck.push_back(temp);
						ycheck.push_back(temp2+1);
					}
					field[temp][temp2]=BLANK;
				}
				break;
			default:
				break;
			}
}
void SaveMap(char *filename) {
	
	FILE *file=fopen(filename,"w");
	if (file) {
		fprintf(file,"%d\n%d\n",gameengine.width,gameengine.height);
		for (int temp=0;temp<gameengine.width;temp++)
			for (int temp2=0;temp2<gameengine.height;temp2++)
				fputc(gameengine.field[temp][temp2],file);
			
	}
	
}
void LoadMap(char *filename) {
	FILE *file=fopen(filename,"r");
	int width=0,height=0;
	if (file) {
		fscanf(file,"%d\n%d\n",&width,&height);
		for (int temp=0;temp<width;temp++)
			for (int temp2=0;temp2<height;temp2++)
				gameengine.field[temp][temp2]=fgetc(file);
	}
}
void engine::Process(void) {
	Redraw();
	runbutton.Process();
	toolswindow.ProcessAll();
	save.ProcessAll();
	load.ProcessAll();
	if (gameinput.leftclicked) {
		if (gameinput.KeyPressed(DIK_LCONTROL)||gameinput.KeyPressed(DIK_RCONTROL)) 
			Fill(gameinput.mousex/16,gameinput.mousey/16);
			else Plot(tool,gameinput.mousex/16,gameinput.mousey/16);
	} 
	if ((gameinput.KeyPressed(DIK_LCONTROL)||gameinput.KeyPressed(DIK_RCONTROL))&&gameinput.KeyPressed(DIK_S))
		save.GiveMessage(CONTROL_ACTIVATE,1,0);
	if ((gameinput.KeyPressed(DIK_LCONTROL)||gameinput.KeyPressed(DIK_RCONTROL))&&gameinput.KeyPressed(DIK_L))
		load.GiveMessage(CONTROL_ACTIVATE,1,0);
	if (state==1) {
		if (gameinput.KeyPressed(DIK_SPACE)) {
			SaveState();
			state=2;
		}
	}
	if (state==2) {
		if (gameinput.KeyPressed(DIK_END)) {
			LoadState();
			state=1;
		}else ProcessField();
	}
}
void engine::Redraw(void) {
	RECT rect = {0,0,16,16};
	for (int temp=0;temp<width;temp++)
		for (int temp2=0;temp2<height;temp2++)
			drawing.DrawWithoutInvisible(temp*16,temp2*16,start+field[temp][temp2],&rect);
}
void engine::Load(void) {
	
	
	Resize(40,40);
	start = drawing.LoadSurface("blank.bmp");
	drawing.LoadSurface("fungus.bmp");
	drawing.LoadSurface("brickwall.bmp");
	drawing.LoadSurface("player.bmp");
	drawing.LoadSurface("grass.bmp");
	drawing.LoadSurface("boulder.bmp");
	drawing.LoadSurface("diamond.bmp");
	drawing.LoadSurface("fire.bmp");
}

void engine::Resize(int width2,int height2) {
	for (int temp=0;temp<width;temp++)
		delete [] field[temp];
	delete [] field;
	field = new char*[width2];
	for (temp=0;temp<width2;temp++)
		field[temp] = new char[height2];
	for (temp=0;temp<width2;temp++)
		for (int temp2=0;temp2<height2;temp2++)
			field[temp][temp2]=0;
	width=width2;
	height=height2;
}

void engine::Plot(int newval,int x,int y) {
	if (x >=0 && y >=0 && x < width && y < height)
		field[x][y]=newval;
}

void engine::Fill(int x,int y) {
	unsigned char target = field[x][y];
	bool **check = new bool*[width];
	for (int temp=0;temp<width;temp++)
		check[temp] = new bool[height];
	for (temp=0;temp<width;temp++)
		for (int temp2=0;temp2<height;temp2++)
			check[temp][temp2]=false;
	check[x][y] = true;
	bool fine = false;
	while (!fine) {
		fine=true;
		for (temp=0;temp<width;temp++)
			for (int temp2=0;temp2<height;temp2++)
				if (check[temp][temp2]) {
					field[temp][temp2]=tool;
					if (temp&&!check[temp-1][temp2]&&field[temp-1][temp2]==target) {
						check[temp-1][temp2]=true;
						fine=false;
					}
					if (temp<width-1&&!check[temp+1][temp2]&&field[temp+1][temp2]==target) {
						check[temp+1][temp2]=true;
						fine=false;
					}
					if (temp2&&!check[temp][temp2-1]&&field[temp][temp2-1]==target) {
						check[temp][temp2-1]=true;
						fine=false;
					}
					if (temp2<height-1&&!check[temp][temp2+1]&&field[temp][temp2+1]==target) {
						check[temp][temp2+1]=true;
						fine=false;
					}

				}
	}
}

