#include <iostream>
#include <vector>
using namespace std;

// Kiểm tra nước đi có hợp lệ hay không
bool isValidMove(int board[][], int N, int row, int col) {
    return (row >= 0 && row < N && col >= 0 && col < N && board[row][col] == -1);
}

// In bàn cờ
void printBoard(int board[][], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

// Hàm quay lui giải bài toán mã đi tuần
bool solveKnightTour(int board[][], int N, int row, int col, int moveCount) {
    // Đánh dấu ô hiện tại là đã đi qua
    board[row][col] = moveCount;

    // Nếu đã đi qua tất cả các ô trên bàn cờ, trả về true
    if (moveCount == N * N) {
        return true;
    }

    // Các bước di chuyển hợp lệ của quân mã
    int moves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

    // Tạo ma trận điểm để lưu trữ số lần thử di chuyển từ mỗi ô
    vector<vector<int>> scores(N, vector<int>(N, 0));

    // Tính điểm cho các ô tiếp theo
    for (int i = 0; i < 8; i++) {
        int nextRow = row + moves[i][0];
        int nextCol = col + moves[i][1];

        // Kiểm tra nếu nước đi tiếp theo hợp lệ
        if (isValidMove(board, N, nextRow, nextCol)) {
            // Tăng điểm của ô tiếp theo
            scores[nextRow][nextCol]++;
        }
    }

    // Thử các ô tiếp theo theo thứ tự điểm giảm dần
    for (int i = 0; i < 8; i++) {
        // Tìm ô tiếp theo có điểm cao nhất
        int maxScore = -1;
        int nextRow, nextCol;

        for (int j = 0; j < 8; j++) {
            int nextRow = row + moves[j][0];
            int nextCol = col + moves[j][1];

            // Kiểm tra nếu nước đi tiếp theo hợp lệ và có điểm cao hơn
            if (isValidMove(board, N, nextRow, nextCol) && scores[nextRow][nextCol] > maxScore) {
                maxScore = scores[nextRow][nextCol];
                nextRow = nextRow;
                nextCol = nextCol;
            }
        }

        // Nếu có ô tiếp theo hợp lệ, tiến hành di chuyển đến ô đó
        if (maxScore != -1) {
            if (solveKnightTour(board, N, nextRow, nextCol, moveCount + 1)) {
                return true;
            }
        }
    }

    // Nếu không tìm thấy lời giải, trả về false và bỏ đánh dấu ô hiện tại
    board[row][col] = -1;
    return false;
}

// Hàm giải bài toán mã đi tuần
void knightTour(int N) {
    // Tạo bàn cờ
    int board[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1;
        }
    }

    // Điểm khởi đầu
    int startRow = 0;
    int startCol = 0;
    int moveCount = 1;

    // Thực hiện giải bài toán mã đi tuần
    if (solveKnightTour(board, N, startRow, startCol, moveCount)) {
        cout << "Lời giải:" << endl;
        printBoard(board, N);
    } else {
        cout << "Không tìm thấy lời giải!" << endl;
    }
}

int main() {
    int N;
    cout << "Nhập kích thước bàn cờ (N x N): ";
    cin >> N;
    knightTour(N);
    return 0;
}
