#include "fsm.h"

// This is a finite state machine realisation based on switch-case statement.
/*

Функция sigact() описывает логику переключения состояний.
    States are checked in order specified in function sigact().
    It enters a state-case which it corresponds to, where begins another
switch-case statement. Inner switch-case statement is looking for a signal given
by get_signal(). After finding it makes some action and switches state to the
next one.

    Pros:
        1) Less memory usage.
    Cons:
        1) A lot of codelines.
*/

signals get_signal(int user_input) {
  signals rc = NOSIG;

  switch (user_input) {
    
        case KEY_UP:
      rc = Up;
      break;
      case KEY_DOWN:
      rc = Down;
      break;
    case KEY_LEFT:
      rc = Left;
      break;
    case KEY_RIGHT:
      rc = Right;
      break;
    case ESCAPE:
      rc = Terminate;
      break;
    case ENTER_KEY:
      rc = Start;
      break;
    case ' ':
      rc = Action;
      break;
    case 'p':
       rc = Pause;
       break;
    default:
      rc = Down; //NOSIG;// ; //
      break;
  }
  return rc;
}

// void moveleft(game_stats_t *gb) {
//  if (!collisionLeft(gb->fnow, gb)) refreshFigure(gb->fnow, -1, 0);
//}

void moveright(figura *f, game_stats_t *gb) {
  if (!collisionRight(f, gb)) refreshFigure(f, 1, 0);
}

void movedown(UserAction_t *state, figura *f, game_stats_t *gb) {
  if (!collisionDown(f, gb))
    refreshFigure(f, 0, 1);
  else {
    figuraGamefield(gb, f);
    // TO DO score
    if (!collisionUp(f, gb)) {
      swapFigure(gb->fnow, gb->fnext);
      // f = gb->fnow;
      hideFigure(gb->fnext);
      initFigure(gb->fnext);

      refreshFigure(gb->fnext, 0, 0);
      // TO DO maybe  used showFigure();
    } else
      *state = Terminate;
  }
}

void rotate(figura *f, game_stats_t *gb) {
  hideFigure(f);
  rotateFigure(f, gb);
  showFigure(f);
}

//void on_start_state(signals sig, frog_state *state, game_stats_t *game) {
//  switch (sig) {
//    case Start:
    //  *state = SPAWN;
void start(game_stats_t *game){  
  hideIntro();
  initFigure(game->fnow);  // инициализируем фигуру
  initFigure(game->fnext);
  showFigure(game->fnow);

  game->fnext->x = R_NEXT_X;
  game->fnext->y = R_NEXT_Y;

  showFigure(game->fnext);
}

void on_moving_state(UserAction_t *state, //board_t *map,
                     player_pos *frog_pos, figura *f, game_stats_t *gamestats) {
  switch (*state) {
      // case MOVE_UP:
      //   moveup(frog_pos); // не используется т.е. убрать
      //   break;

    //case Down:
    //  movedown(state, f, gamestats);
    //  break;



    case ESCAPE_BTN:
      *state = Terminate; //EXIT_STATE;
      break;
    //case PAUSE_BTN:
    //  while (GET_USER_INPUT <> 'p') {}
    //  break;
    default:
       
      break;
  }

}


//  add_proggress(map); // TO DO DEL
//    stats->level++;
//    stats->speed++;
//    frogpos_init(frog_pos);
//    // print_finished(map);


void sigact(UserAction_t *state, game_stats_t *gamestats,
            //board_t *map, 
            player_pos *frog_pos, figura *fnow) {
  switch (*state) {
    case Start:
      start(gamestats);
      break;
  case Pause:
  do {*state = get_signal(GET_USER_INPUT);}      while ( *state != Start );
     break;
  case Left:
      moveleft(fnow, gamestats);
      break;
   case Right:
      moveright(fnow, gamestats);  // сдвинуть фигуру вправо
      break;
   case Down: //MOVING:
      on_moving_state(state,  frog_pos, fnow, gamestats); //map,
      break;
   case Action:
      rotate(fnow, gamestats);
      break;
    case Terminate:
    	gameOver(); // gameOVER thanks for game
        napms(2000); //func sleep for at least ms milliseconds
        *state = Terminate;
      break;
      
    default:

      break;
      	 
  }

}
