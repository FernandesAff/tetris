#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void criar_tela(char tela[][25]){
	int i,j;

	for(i=0;i<15;i++){
		for(j=0;j<25;j++){
			tela[i][j]=' ';
		}
	}	
}

void mostrar_tela(char tela[][25]){
	int i,j;

	mvaddch(5, 0, '=');
	mvaddch(5, 1, ACS_RARROW);
	mvaddch(5, 29, ACS_LARROW);
	mvaddch(5, 30, '=');
	
	for(i=0;i<15;i++){
		for (j=0;j<25;j++){
			mvaddch(i+1, j+2, tela[i][j]);
		}
	}

	for(i=0;i<17;i++){
		for(j=0;j<14;j++){
			if(i==0){
				if(j==0){
					mvaddch(i, j+2, ACS_ULCORNER);
				}
				else{
					if(j==13){
						mvaddch(i, j+2, ACS_URCORNER);
					}
					else{
						mvaddch(i, j+2, ACS_HLINE);
					}
				}
			}
			else{
				if(i!=16){
					if(j==0){
						mvaddch(i, j*2+2, ACS_VLINE);
					}
					else
						if(j==13){
							mvaddch(i, j*2+1, ACS_VLINE);
						}
				}
				else{
					if(j==0){
						mvaddch(i, j+2, ACS_LLCORNER);
					}
					else{
						if(j==13){
							mvaddch(i, j+2, ACS_LRCORNER);
						}
						else{
							mvaddch(i, j+2, ACS_HLINE);
						}
					}
				}
			}
		}
	}
}