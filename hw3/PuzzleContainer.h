/**
 * İdil Atmaca 22002491 CS201 HW3
 */
#include <iostream>
using namespace std;


namespace {
    void shapeConverter(unsigned char shape, int &down, int &up, int &right, int &left) {
        down = shape % 4;
        up = (shape / 4) % 4;
        right = (shape / 16) % 4;
        left = shape / 64;
    }
}
class PuzzleRow {
    private:

    struct PuzzlePiece{
    char shape;
    int rowindex;
    int colindex;
    PuzzlePiece* pNext;
    };


    PuzzlePiece* puzzleHead;
    PuzzlePiece* puzzleTail;
    PuzzleRow* rowNext;
    int puzNum;
    int rowindex;
    int maxSize; //equals to puzzleContainer width
    public:
    PuzzleRow( int size, int rowindex);
    ~PuzzleRow();
    int getRowIndex();
    bool canBePlaced( int col, unsigned char shape);
    void setNext( PuzzleRow* next );
    PuzzleRow* getNext();
    bool insert( int index, char shape );
    bool remove( int index );
    bool isEmpty();
    int findPiece(char shape);
    unsigned char getPiece(int index );
    bool isComplementary(int s1, int s2);
    void printRow();

};


class PuzzleContainer{
    private:
    PuzzleRow* rowLists;
    PuzzleRow* rowTail;
    int height;
    int width;
    public:
    PuzzleContainer( int h, int w);
    ~PuzzleContainer();
    PuzzleRow* getRow( int index );
    bool insertRow( int index );
    bool removeRow( int index );
    bool addPiece( int row, int col , char shape );
    bool removePiece(int row, int col);
    int getHeight();
    int getWidth();
    void showPiece(int row, int col);
    void displayContainer();
    bool canBePlaced(int row, int col, unsigned char shape);
    void showColumn(int col);
    void showRow(int row);
    void printPiece(unsigned char shape);
    void findPiece(char shape);
    string binaryToString(int a);
    bool isComplemantary(int s1, int s2);
};
