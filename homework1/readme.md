*2048 from djyU201611827*

**本程序是一个用python语言写的2048的小游戏，主要有初始化、数字处理、运行三个模块，运行后'W,w'代表向上移动，'S，s'代表向下移动，'A，a'代表向左移动，'D,d'代表向右移动，移动代表所有数字向同一个方向移动，相同数字在一起即可叠加（本程序中可多次叠加，即2，2，2，2移动后变为8），达到2048时游戏结束，获得胜利，当16个格子占满并无法移动时游戏结束了，失败**

**代码如下，直接运行即可**

```python
import random

m = [[0, 0, 0, 0],
     [0, 0, 0, 0],
     [0, 0, 0, 0],
     [0, 0, 0, 0]]

def display(m, score):
        #显示界面,并用矩阵值代替字符串
        print('{0} {1} {2} {3}'.format(m[0][0], m[0][1], m[0][2], m[0][3]))
        print('{0} {1} {2} {3}'.format(m[1][0], m[1][1], m[1][2], m[1][3]))
        print('{0} {1} {2} {3}'.format(m[2][0], m[2][1], m[2][2], m[2][3]))
        print('{0} {1} {2} {3}'.format(m[3][0], m[3][1], m[3][2], m[3][3]),
'    Total score: ', score)
def init(m):
#初始值随机
        for i in range(4):
               m[i]=[2 if random.randrange(100)>79 \
                       else 0 for x in m[i]]
    #另一种方法 for i in range(4)
    #m[i]=2 if randrange(100)>79 else 0 这样开始有值的网格数量较少
def getnear(matrix, direction):

        '''
        对齐非零的数字
        direction == 'left'：向左对齐
        direction == 'right'：向右对齐
        '''

        # 移除列表中的0
        for i in range(matrix.count(0)):
                matrix.remove(0)

        zeros = [0 for x in range(4 - len(matrix))]

        # 在非0数字的一侧补充0

        if direction == 'left':
                matrix.extend(zeros)
        else:
                matrix[:0] = zeros

def addSame(matrix, direction):

        #在列表查找相同且相邻的数字相加, 找到符合条件的返回True，否则返回False,同时还返回增加的分数

        score = 0
        if direction == 'left':
                for i in [0, 1, 2]:
                        if matrix[i] ==matrix[i+1] != 0:
                                matrix[i] *= 2
                                matrix[i+1] = 0
                                score += matrix[i]
                                return {'bool':True, 'score':score}

        else:
                for i in [3, 2, 1]:
                        if matrix[i] == matrix[i-1] != 0:
                                matrix[i-1] *= 2
                                matrix[i] = 0
                                score += matrix[i-1]
                                return {'bool':True, 'score':score}
        return {'bool':False, 'score':score}

def handle(matrix, direction):
        #处理一行（列）中的数据，得到最终的该行（列）的数字状态值, 返回得分
       #向上变为向左的转置，向下变为向右的转置

        totalScore = 0
        getnear(matrix, direction)
        result = addSame(matrix, direction)
        while result['bool'] == True:
                #当实现加法加分后重新进行getnear和addsame直到加不动为至，在网上看到有一种2048程序是getnear（addsame（getnear）），最后的结果不同
                totalScore += result['score']
                getnear(matrix, direction)
                result = addSame(matrix, direction)
        return totalScore


def operation(m):
       #分为两步，求出状态值，再记录得分

        totalScore = 0
        gameOver = False
        direction = 'left'
        op = input('operator:')
        if op in ['a', 'A']:    # 向左移动
                direction = 'left'
                for row in range(4):
                        totalScore += handle(m[row], direction)
        elif op in ['d', 'D']:  # 向右移动
                direction = 'right'
                for row in range(4):
                        totalScore += handle(m[row], direction)
        elif op in ['w', 'W']:  # 向上移动
                direction = 'left'
                for col in range(4):
                        # 将矩阵中一列复制到一个列表中然后处理
                        matrix = [m[row][col] for row in range(4)]
                        totalScore += handle(matrix, direction)
                        # 从处理后的列表中的数字覆盖原来矩阵中的值
                        for row in range(4):
                                m[row][col] = matrix[row]
        elif op in ['s', 'S']:  # 向下移动
                direction = 'right'
                for col in range(4):
                        # 同上
                        matrix = [m[row][col] for row in range(4)]
                        totalScore += handle(matrix, direction)
                        for row in range(4):
                                m[row][col] = matrix[row]
        else:
                print('Invalid input, please enter a charactor in [W, S, A, D] or the lower')
                return {'gameOver':gameOver, 'score':totalScore}

        # 统计空白区域数目 N

        N = 0
        for q in m:
            N += q.count(0)
      # 不存在剩余的空白区域时，游戏结束
        if N == 0:
                gameOver = True
                return {'gameOver':gameOver, 'score':totalScore}

        # 每次op按比例产生新数字

        num = random.choice([2, 2, 2, 4])
        k = random.randrange(1, N+1)
        n = 0
        for i in range(4):
                for j in range(4):
                        if m[i][j] == 0:
                                n += 1
                                if n == k:
                                        m[i][j] = num
                                        break

        return {'gameOver':gameOver, 'score':totalScore}

init(m)
score = 0
print('Input：W S A D press <CR>.')
while True:
        display(m, score)
        result = operation(m)
        if result['gameOver'] == True:
                print('faild')
                print('Your total score:', score)
        else:
                score += result['score']
                if score >= 2048:
                        print('2048！')
                        print('Your total score:', score)
