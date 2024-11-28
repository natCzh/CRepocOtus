#ifndef _FIELD_GAME_H_
#define _FIELD_GAME_H_

#include <QWidget>
#include <QObject>

class QAction;

class FieldGame : public QWidget
{
    Q_OBJECT
public:

    explicit FieldGame(QWidget *parent = 0);
    ~FieldGame(){}
};

#endif /* _FIELD_GAME_H_ */
