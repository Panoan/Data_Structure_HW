#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;

/* Sample
[1,1,1,1,1,1,1,1,1],
[1,2,0,1,0,0,0,0,1],
[1,0,0,0,0,1,1,0,1],
[1,0,1,1,1,0,0,0,1],
[1,0,0,0,1,0,1,0,1],
[1,0,1,0,0,0,1,0,1],
[1,0,1,1,1,0,1,1,1],
[1,0,0,0,0,0,0,3,1],
[1,1,1,1,1,1,1,1,1]
 */

//store the coordinate of a point
class coordinate {
public:
    int r; //row
    int c; //column
    
/* 
the coordinate (r,c) represents 
the intersection of the rth row 
and the cth column 
*/

    coordinate() {
        r = -1; c = -1;
    }
    coordinate(int r, int c) {
        this->r = r;
        this->c = c;
    }

    //get the coordinates of the adjacent points in four directions
    coordinate up() const {
        return coordinate(r-1, c);
    }
    
    coordinate down() const {
        return coordinate(r+1, c);
    }
    coordinate left() const {
        return coordinate(r, c-1);
    }
    coordinate right() const {
        return coordinate(r, c+1);
    }
};

//overload <<
ostream& operator <<(ostream& os, coordinate co) {
    //output: the actual coordinate
    os << "(" << co.r + 1 << "," << co.c + 1 << ")";
    return os;
}

//dynamic 2-d array
class d2a {
public:
    int wid = 0, len = 0;
    int **binary_arr;

    d2a(int wid, int len) {
        this->wid = wid; this->len = len;
        binary_arr = new int* [len + 1];
        for(int i = 0; i < len; i++)
            binary_arr[i] = new int[wid+1];
    }

    ~d2a() {
        for(int i = 0; i < len; i++) {
            delete[] binary_arr[i];
        }
        delete[] binary_arr;
    }
    void input() {
        for(int i = 0; i < len; i++) {
            for(int j = 0; j < wid; j++) {
                cin >> binary_arr[i][j];
            }
        }
    }

    void output() {
        for(int i = 0; i < len; i++) {
            for(int j = 0; j < wid; j++) {
                cout << setw(2) << binary_arr[i][j];
            }
            cout << endl;
        }
    }

    //return the coordinate of the number where it first shows
    coordinate Find(int g) {
        for(int i = 0; i < wid; i++) {
            for(int j = 0; j < len; j++) {
                if (g == binary_arr[i][j]) {
                    coordinate Point(i, j);
                    return Point;
                }
            }
        }
        return coordinate(-1, -1);
    }

    //return the value of some_point
    //using coordinate
    int loc(coordinate some_point) {
        return binary_arr[some_point.r][some_point.c];
    }
    //directly using two integers representing row and column
    int loc(int r, int c) {
        return binary_arr[r][c];
    }

    void flag(coordinate some_point, int i) {
        binary_arr[some_point.r][some_point.c] = i;
    }

    void print() {
        for(int i = 0; i < len; i++) {
            for(int j = 0; j < wid; j++) {
                cout << setw(2) << binary_arr[i][j];
            }
            cout << endl;
        }
    }
    void clear() {
        for(int i = 0; i < len; i++) {
            for(int j = 0; j < wid; j++) {
                this->binary_arr[i][j] = 0;
            }
        }
    }
};

//BFS
void BFS(d2a& maze, vector<coordinate>& route) {
    d2a flag_map(maze.len, maze.wid);
    //fill flag_map with 0
    flag_map.clear();

    queue<coordinate> q;
    q.push(route[0]);
    int i = 1;
    coordinate end = maze.Find(3);
    while(!q.empty()) {
        coordinate curr = q.front(); q.pop();
        if(maze.loc(curr) == 3) break; //endpoint
        flag_map.flag(curr, i); //flag if this point has been visited
        if(!maze.loc(curr.up()) && flag_map.loc(curr.up()) == 0)  
            q.push(curr.up());
        if(!maze.loc(curr.down()) && flag_map.loc(curr.down()) == 0)  
            q.push(curr.down());
        if(!maze.loc(curr.left()) && flag_map.loc(curr.left()) == 0)  
            q.push(curr.left());
        if(!maze.loc(curr.right()) && flag_map.loc(curr.right()) == 0)  
            q.push(curr.right());
        i++;        //each time take a step on 4 directions, and the current step is ith step
    }
    coordinate curr = end;
    while(i > 2) {
        if(flag_map.loc(curr.up()) == i-1) {
            route.insert(route.begin() + 1, curr.up());
            curr = curr.up();
        }
        if(flag_map.loc(curr.down()) == i-1) {
            route.insert(route.begin() + 1, curr.down());
            curr = curr.down();
        }
        if(flag_map.loc(curr.left()) == i-1) {
            route.insert(route.begin() + 1, curr.left());
            curr = curr.left();
        }
        if(flag_map.loc(curr.right()) == i-1) {
            route.insert(route.begin() + 1, curr.right());
            curr = curr.right();
        }
        i--;
    }
}

//DFS
void DFS(d2a& maze, vector<coordinate>& route) {
    d2a flag_map(maze.len, maze.wid);
    //fill flag_map with 0
    flag_map.clear();
    
    stack<coordinate> s;
    s.push(route[0]);
    int i = 1;
    coordinate end = maze.Find(3);
    while(!s.empty()) {
        coordinate curr = s.top(); s.pop();
        if(maze.loc(curr) == 3) break; //endpoint
        flag_map.flag(curr, i); //flag if this point has been visited
        bool
            U = maze.loc(curr.up()) == 0 && flag_map.loc(curr.up()) == 0 ,
            D = maze.loc(curr.down()) == 0 && flag_map.loc(curr.down()) == 0,
            L = maze.loc(curr.left()) == 0 && flag_map.loc(curr.left()) == 0,
            R = maze.loc(curr.right()) == 0&& flag_map.loc(curr.right()) == 0;
        if(U) s.push(curr.up());
        if(D) s.push(curr.down());
        if(L) s.push(curr.left());
        if(R) s.push(curr.right());
        if (maze.loc(curr.up()) == 3 || maze.loc(curr.down()) == 3 ||
            maze.loc(curr.left()) == 3 || maze.loc(curr.right()) == 3)
            break;
        if (!s.empty() && !U && !D && !L && !R) {
            coordinate last_split = s.top();
            int last_split_up_flag  = flag_map.loc(last_split.up());
            int last_split_down_flag = flag_map.loc(last_split.down());
            int last_split_right_flag = flag_map.loc(last_split.right());
            int last_split_left_flag = flag_map.loc(last_split.left());
            i = max(max(last_split_up_flag, last_split_down_flag), max(last_split_right_flag, last_split_left_flag));
        }
            
        i++;        //each time take a step on 4 directions, and the current step is ith step
    } //search end

    //put these coordinates into the route vector
    coordinate curr = end;
    while(i > 1) {
        /* if(flag_map.loc(curr.up()) == i) {
            route.insert(route.begin() + 1, curr.up());
            curr = curr.up();
        }
        if(flag_map.loc(curr.down()) == i) {
            route.insert(route.begin() + 1, curr.down());
            curr = curr.down();
        }
        if(flag_map.loc(curr.left()) == i) {
            route.insert(route.begin() + 1, curr.left());
            curr = curr.left();
        }
        if(flag_map.loc(curr.right()) == i) {
            route.insert(route.begin() + 1, curr.right());
            curr = curr.right();
        }
        i--; */
        //the previous solution cannot find the shortest route

        //show the neighbours
        struct Node {
            coordinate c;
            int flag;
        };
        
        Node neighbours[4];
        neighbours[0].c = curr.up();
        neighbours[0].flag = flag_map.loc(neighbours[0].c);
        neighbours[1].c = curr.down();
        neighbours[1].flag = flag_map.loc(neighbours[1].c);
        neighbours[2].c = curr.left();
        neighbours[2].flag = flag_map.loc(neighbours[2].c);
        neighbours[3].c = curr.right();
        neighbours[3].flag = flag_map.loc(neighbours[3].c);
        
        int min_neighbour_flag = 1000000;
        for(int i = 0; i < 4; i++) {
            if(neighbours[i].flag == 0)
                continue;
            else if (neighbours[i].flag < min_neighbour_flag) {
                min_neighbour_flag = neighbours[i].flag;
                curr = neighbours[i].c;
            }
        }
        i = min_neighbour_flag;
        route.insert(route.begin() + 1, curr);
    }
}

int main() {
    d2a maze(9, 9); 
    maze.input();

    //get the start and end point of the maze
    coordinate start = maze.Find(2);
    coordinate end = maze.Find(3);

    vector<coordinate> route;
    route.push_back(start);
    
    //choose BFS or DFS
    while(1){
        int choice;
        cout << "Choose algorithm:\n1. BFS\n2. DFS\n";
        cin >> choice;
        if(choice == 1) {
            BFS(maze, route);
            break;
        } else if(choice == 2) {
            DFS(maze, route);
            break;
        }
    }
    
    int Size = route.size();
    for (int i = 1; i < Size; i++) {
        cout << route[i] << "->";
        //line breaker to prevent a too long line
        if (i % 5 == 0) cout << endl; 
    }
    cout << end;
    return 0;
}

/* 
Sample Input:
1 1 1 1 1 1 1 1 1
1 2 0 0 0 0 0 0 1
1 0 0 1 0 1 1 0 1
1 0 1 1 1 0 0 0 1
1 0 0 0 1 0 1 0 1
1 0 1 0 0 0 1 0 1
1 0 1 1 1 0 1 1 1
1 0 0 0 0 0 0 3 1
1 1 1 1 1 1 1 1 1

Sample Output:
(2,2)->(2,3)->(2,4)->(2,5)->(2,6)->
(2,7)->(2,8)->(3,8)->(4,8)->(4,7)->
(4,6)->(5,6)->(6,6)->(6,5)->(6,4)->
(5,4)->(5,3)->(5,2)->(6,2)->(7,2)->
(8,2)->(8,3)->(8,4)->(8,5)->(8,6)->
(8,7)->(8,8)EOF

*/