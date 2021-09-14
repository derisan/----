# 게임공학과 2016180007 김명규
import test
import queue


# 상태를 나타내는 클래스, f(n) 값을 저장한다.
class State:
    def __init__(self, board, goal, depth=0):
        self.board = board
        self.depth = depth
        self.goal = goal

    def expand(self, depth):
        result = []
        for i in range(len(self.board)):
            new_board = self.board[:]
            new_board[depth - 1] = i
            result.append(State(new_board, self.goal, depth))
        return result

    # f(n)을 계산하여 반환한다.
    def f(self):
        return self.h() + self.g()

    # 휴리스틱 함수 값인 h(n)을 계산하여 반환한다.
    # h(n)은 서로 공격하고 있는 퀸의 수이다.
    def h(self):
        cost = 0
        for i in range(len(self.board)):
            for j in range(i + 1, len(self.board)):
                if self.board[i] == self.board[j]:
                    cost += 1
                offset = j - i

                if self.board[i] == self.board[j] - offset or \
                        self.board[i] == self.board[j] + offset:
                    cost += 1

        return cost

    # 시작 노드로부터의 경로를 반환한다.
    def g(self):
        return self.depth

    def __eq__(self, other):
        return self.board == other.board and self.depth == other.depth

    # 상태와 상태를 비교하기 위하여 less than 연산자를 정의한다.
    def __lt__(self, other):
        return self.f() < other.f()

    def __gt__(self, other):
        return self.f() > other.f()

    # 객체를 출력할 때 사용한다.
    def __str__(self):
        return "------------------ f(n)=" + str(self.f()) + "\n" + \
               "------------------ h(n)=" + str(self.h()) + "\n" + \
               "------------------ g(n)=" + str(self.g()) + "\n" + \
               str(self.board)
        "------------------"


print("-------------------------")
print("게임공학과 2016180007 김명규")
print("-------------------------\n")

N = int(input("N의 값을 입력하시오(4, 5가 적당. 6 이상은 너무 느립니다!): "))
solutions = test.get_all_solutions(N)


for goal in solutions:
    initial = [0] * N

    print("Init to Goal: ", initial, "----->", goal)

    open_queue = queue.PriorityQueue()
    open_queue.put(State(initial, goal))

    closed_queue = []
    while not open_queue.empty():

        current = open_queue.get()
        # ------테스트 시 주석 해제-------
        # print(current)
        # -----------------------------
        if current.board == goal:
            print(current)
            print("탐색 성공\n")
            break

        if current.depth == N:
            continue

        for state in current.expand(current.depth + 1):
            if state not in closed_queue:
                open_queue.put(state)
        closed_queue.append(current)


print("-------------------------")
print("게임공학과 2016180007 김명규")
print("-------------------------")
