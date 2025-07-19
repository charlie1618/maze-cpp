#include <bits/stdc++.h>
using namespace std;

void print_grid(vector<vector<vector<bool>>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "+";
            cout << (grid[i][j][0] ? "---" : "   ");
        }
        cout << "+\n";

        for (int j = 0; j < m; j++) {
            cout << (grid[i][j][2] ? "|" : " ");
            cout << "   ";
            //cout << (grid[x][y].visited ? " * " : "   ");
        }
        if(i != n - 1) cout << "|";
        cout << endl;
    }

    for (int i = 0; i < m; i++) {
        cout << "+---";
    }
    cout << "+\n";

    return;
}

vector<vector<vector<bool>>> create_maze(int n, int m) {
    vector<vector<vector<bool>>> grid(
        n, vector<vector<bool>>(
            m, vector<bool>(4, true)
        )
    );
    vector<vector<bool>> conn(n, vector<bool>(m, false));
    vector<vector<int>> walls;

    conn[0][0] = true;
    grid[0][0][2] = false;
    walls.push_back({0, 1, 0});
    walls.push_back({2, 0, 1});

    while(!walls.empty()) {
        /*
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, walls.size() - 1);
        int idx = distrib(gen);
        */
        srand(static_cast<unsigned>(std::time(nullptr)));
        int idx = rand() % walls.size();
        auto wall = walls[idx];
        int dir = wall[0];
        int r = wall[1];
        int c = wall[2];

        if(conn[r][c]) {
            walls.erase(walls.begin() + idx);
            continue;
        }
        else {
            conn[r][c] = true;
            grid[r][c][dir] = false;

            if(dir == 0) grid[r - 1][c][1] = false;
            else if(dir == 1) grid[r + 1][c][0] = false;
            else if(dir == 2) grid[r][c - 1][3] = false;
            else if(dir == 3) grid[r][c + 1][2] = false;

            walls.erase(walls.begin() + idx);
        }

        if(r > 0 && !conn[r - 1][c]) walls.push_back({1, r - 1, c});
        if(r < n - 1 && !conn[r + 1][c]) walls.push_back({0, r + 1, c});
        if(c > 0 && !conn[r][c - 1]) walls.push_back({3, r, c - 1});
        if(c < m - 1 && !conn[r][c + 1]) walls.push_back({2, r, c + 1});
    }

    return grid;
}

int main() {
    int n, m;
    cout << "No. of rows: ";
    cin >> n;
    cout << "No. of columns: ";
    cin >> m;

    auto maze = create_maze(n, m);
    print_grid(maze);

    return 0;
}
