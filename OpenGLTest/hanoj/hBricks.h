#ifndef HBRICKS_H
#define HBRICKS_H

#include "ctObject.h"

class Block;
class ctInput;

class hBricks : public ctObject
{
private:
    QVector <Block*> m_blocks;
    QVector<QVector<Block*>*> m_blockSlots;
    QVector<Block*> m_movingStash;
    //QVector<Block*> m_reservedContainer;
    ctInput * m_input;
    const float m_verticalAligneBlock;
    const float m_horisontalAligneBlock;
    int m_prevColumn;
public:
    hBricks();
    explicit hBricks(ctShaderManager *);
    hBricks(ctShaderManager *, ctScene *, ctInput *);
    hBricks(ctShaderManager *, ctScene *, QGLContext *, ctInput *);
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
    Block* Partition(QVector <Block*> m, int a, int b);
    void Quicksort( QVector <Block*> m, int a, int b);
    /*
int partition<T>( T[] m, int a, int b) where T :IComparable<T>
{
    int i = a;
    for (int j = a; j <= b; j++)         // просматриваем с a по b
    {
        if (m[j].CompareTo( m[b]) <= 0)  // если элемент m[j] не превосходит m[b],
        {
            T t = m[i];                  // меняем местами m[j] и m[a], m[a+1], m[a+2] и так далее...
            m[i] = m[j];                 // то есть переносим элементы меньшие m[b] в начало,
            m[j] = t;                    // а затем и сам m[b] «сверху»
            i++;                         // таким образом последний обмен: m[b] и m[i], после чего i++
        }
    }
    return i - 1;                        // в индексе i хранится <новая позиция элемента m[b]> + 1
}

void quicksort<T>( T[] m, int a, int b) where T : IComparable<T>// a - начало подмножества, b - конец
{                                        // для первого вызова: a = 0, b = <элементов в массиве> - 1
    if (a >= b) return;
    int c = partition( m, a, b);
    quicksort( m, a, c - 1);
    quicksort( m, c + 1, b);
}

//Пример вызова
//double[] arr = {9,1.5,34.4,234,1,56.5};
//quicksort<double>(arr,0,arr.Length-1);
//
     */
};

#endif // HBRICKS_H
