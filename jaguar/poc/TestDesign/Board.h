/* 
 * File:   Board.h
 * Author: cross
 *
 * Created on January 12, 2010, 9:20 PM
 */

#ifndef _BOARD_H
#define	_BOARD_H

#include <QGraphicsScene>

class Board : public QGraphicsScene {
public:
    Board();
    Board(const Board& orig);
    virtual ~Board();
private:

};

#endif	/* _BOARD_H */

