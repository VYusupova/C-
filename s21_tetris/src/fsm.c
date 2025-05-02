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

        \/ TO DO ENTER click second 
*/

UserAction_t get_signal(int user_input) {  // TO DO RENAME
  UserAction_t rc = Down;

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
    case '\n':
      rc = Start;
      break;
    case ' ':
      rc = Action;
      break;
    case 'p':
      rc = Pause;
      break;
    default:
      //rc = Down;
      break;
  }
  return rc;
}

// void moveleft(game_stats_t *gb) {
//  if (!collisionLeft(gb->fnow, gb)) refreshFigure(gb->fnow, -1, 0);
//}

void moveleft(figura *f, game_stats_t *gb) {
  if (!collisionLeft(f, gb)) refreshFigure(f, -1, 0);
}

void moveright(figura *f, game_stats_t *gb) {
  if (!collisionRight(f, gb)) refreshFigure(f, 1, 0);
}

void movedown(/*UserAction_t *userAct,*/ tetris_state *state, figura *f,
              game_stats_t *gb) {
  if (!collisionDown(f, gb))
    refreshFigure(f, 0, 1);
  else {
    figuraGamefield(gb, f);
    score(gb);
    refreshGameField(gb);
    // TO DO score
    if (!collisionUp(f, gb)) {
      swapFigure(gb->fnow, gb->fnext);
      // f = gb->fnow;
      hideFigure(gb->fnext);
      initFigure(gb->fnext);

      refreshFigure(gb->fnext, 0, 0);
      // TO DO maybe  used showFigure();
    } else {
      //*userAct = Terminate;
      *state = GAMEOVER;
    }
  }
}

void rotate(figura *f, game_stats_t *gb) {
  hideFigure(f);
  rotateFigure(f, gb);
  showFigure(f);
}


void gg(game_stats_t *game, tetris_state *state){
      hideIntro();
      initFigure(game->fnow);  // инициализируем фигуру
      initFigure(game->fnext);
      showFigure(game->fnow);
      showFigure(game->fnext);
      *state = MOVING;
}


void started(UserAction_t *userAct, game_stats_t *game, tetris_state *state) {
  switch (*userAct) {
    case Start:
      gg(game,state);
      break;
    case Terminate:
      *state = GAMEOVER;
      break;
    case Pause:
    //userAct = Start;
      *state = GAME;
      break;
    default:

      break;
  }
}


void moved(UserAction_t *userAct, tetris_state *state, game_stats_t *gamestats,
            figura *fnow)
{
    switch (*userAct)
    {
        case Left:
             moveleft(fnow, gamestats);
            break;
        case Right:
             moveright(fnow, gamestats); 
            break;
        case Up:
            break;
        case Down:
             movedown(state, fnow, gamestats); 
            break;
        case Action:
            rotate(fnow, gamestats);
            break;
        case Pause:
            //while(GET_USER_INPUT != 'p') {};
            break;
        case Terminate:
            *state = GAMEOVER;
            break;
        default:
        //movedown(state, fnow, gamestats);
            break;
    }
}


//  add_proggress(map); // TO DO DEL
//    stats->level++;
//    stats->speed++;
//    frogpos_init(frog_pos);
//    // print_finished(map);

void sigact(UserAction_t *userAct, tetris_state *state, game_stats_t *gamestats,
            figura *fnow) {
  print_stats(gamestats);
      // napms(2000); //func sleep for at least ms milliseconds
  switch (*state) {
    case GAME:
      started(userAct, gamestats, state);
      break;
    case MOVING:
      moved(userAct, state, gamestats,  fnow);
      break;
    case GAMEOVER:
      gameOver();  // gameOVER thanks for game
      timeout(700);
      break;
    default:
      break;
  }
}
