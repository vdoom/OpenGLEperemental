#ifndef HBRICKS_H
#define HBRICKS_H

#include "ctObject.h"
#include <QPoint>
class Block;
class ctInput;
class ctPlane;

class hBricks : public ctObject
{
private:
    QVector<Block*> m_blocks;
    QVector<QVector<Block*>*> m_blockSlots;
    QVector<Block*> m_movingStash;
    //QVector<Block*> m_reservedContainer;
    ctInput * m_input;
    const float m_verticalAligneBlock;
    const float m_horisontalAligneBlock;
    int m_prevColumn;
    ctPlane * m_winText;
	//----------------------------------------
	QVector<QVector<QVector<QPoint> > > m_savedSteps;
public:
    hBricks();
    explicit hBricks(ctShaderManager *);
    hBricks(ctShaderManager *, ctScene *, ctInput *);
    hBricks(ctShaderManager *, ctScene *, QOpenGLContext *, ctInput *);
    virtual ~hBricks();

    virtual void Update();
    virtual void Draw();//=0;
    virtual void Init();//=0;
    //-----------------------------------------------------------
    void SetInput(ctInput*);
    void AligneBlocks(bool t_fast = false);
    void ManageCollide();
    void ResetBlocks();
    void ReinitColumns();//(QVector<Block *> t_blocks);
    int GetColByPos(QVector2D t_pos);
    void DropBlock(int t_col);
    void TakeBlock(int t_col, int t_row);
    QPoint FindBlock(Block *t_block);
    void GenerateBlocks();
    bool IsWin();
    void SetProjectionMatrixtt(ctMatrix4 & t_projMat);
    void SetProjectionMatrixtt(QMatrix4x4 & t_projMat);

//------------------------------------------------------------------------------------
    int MoreThen(Block* t_block1, Block* t_block2);
    void Swap(Block* t_block1, Block* t_block2);
    int Partition(QVector <Block*>* m, int a, int b);
    void Quicksort( QVector <Block*>* m);//, int a, int b);
    void SetWinPlane(ctPlane* t_plane);
//------------------------------------------------------------------------------------
	void SaveStep();
	void UndoStep();
	int FindeBlockIndex(QPoint);
};

#endif // HBRICKS_H
