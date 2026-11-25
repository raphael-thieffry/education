#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define H 7
#define W 11

char maze[H][W] = { "+-+---+---+",
                    "| |     |#|",
                    "| | --+ | |",
                    "| |   | | |",
                    "| +-- | | |",
                    "|     |   |",
                    "+-----+---+" };
					
void draw () {
  int i, j;
  for (i = 0; i < H; i++) {
    for (j = 0; j < W; j++)
      printf ("%c", maze[i][j]);
    printf ("\n");
  }
  printf ("\n");
}


int main (int argc, char *argv[]) {
  int x, y;     //Player position
  int ox, oy;   //Old player position
  int i = 0;    //Iteration number
#define ITERS 28
  char program[ITERS];
	 
  x = 1;
  y = 1;
  maze[y][x]='X';

  //  printf ("Maze dimensions: %dx%d\n", W, H);
  //  printf ("Player pos: %dx%d\n", x, y);
  //  printf ("Iteration no. %d\n",i);
  //  printf ("Program the player moves with a sequence of 'w', 's', 'a' and 'd'\n");
  //  printf ("Try to reach the price(#)!\n");
 
  //Draw the maze
  //  draw ();
  
  read(0,program,ITERS);

  while(i < ITERS) {
    ox = x;    //Save old player position
    oy = y;
	
    switch (program[i]) {
    case 'w':
      y--;
      break;
    case 's':
      y++;
      break;
    case 'a':
      x--;
      break;
    case 'd':
      x++;
      break;
    default:
      printf("Wrong command! (only w, s, a, d accepted!)\n");
      printf("You lose!\n");
      exit(-1);
    }
		
    if (maze[y][x] == '#') {
      printf ("You win!\n");
      printf ("Your solution <%42s>\n",program);
      //      exit(1);
      abort();
    }
		
    if (maze[y][x] != ' ' &&
	!((y == 2 && maze[y][x] == '|' && x > 0 && x < W))) {
      x = ox;
      y = oy;
    }

    //Print new maze state and info...
    //    printf ("Player pos: %dx%d\n", x, y);
    //    printf ("Iteration no. %d. Action: %c.",i,program[i]);
    printf ("%s", ((ox==x && oy==y)?"Blocked!\n":""));
			
    if (ox==x && oy==y) {
      printf("You lose\n");
      exit(-2);
    }
		
    maze[y][x]='X';
    //    draw();          //draw it
		
    i++;
    //   sleep(1); //me wait to human
  }
	
  printf("You lose\n");

}
