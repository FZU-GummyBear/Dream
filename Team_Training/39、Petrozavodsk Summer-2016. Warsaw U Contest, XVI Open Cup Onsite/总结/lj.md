| Run ID | Time    | Size | Problem | Language | Result              | Failed test | View source                                                  | View report |
| ------ | ------- | ---- | ------- | -------- | ------------------- | ----------- | ------------------------------------------------------------ | ----------- |
| 1807   | 4:57:59 | 2571 | E       | g++0x    | OK                  | N/A         | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1807&action=36) | N/A         |
| 1805   | 4:49:15 | 2196 | B       | g++0x    | Wrong answer        | 7           | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1805&action=36) | N/A         |
| 1803   | 4:40:58 | 2117 | B       | g++0x    | Wrong answer        | 7           | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1803&action=36) | N/A         |
| 1793   | 4:31:02 | 1883 | B       | g++0x    | Run-time error      | 7           | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1793&action=36) | N/A         |
| 1750   | 3:04:53 | 2919 | A       | g++0x    | OK                  | N/A         | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1750&action=36) | N/A         |
| 1744   | 2:57:39 | 2914 | A       | g++0x    | Wrong answer        | 18          | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1744&action=36) | N/A         |
| 1740   | 2:54:16 | 2915 | A       | g++0x    | Wrong answer        | 18          | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1740&action=36) | N/A         |
| 1703   | 1:57:48 | 2256 | H       | g++0x    | OK                  | N/A         | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1703&action=36) | N/A         |
| 1679   | 1:26:29 | 2385 | J       | g++0x    | OK                  | N/A         | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1679&action=36) | N/A         |
| 1651   | 0:29:37 | 1344 | D       | g++0x    | OK                  | N/A         | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1651&action=36) | N/A         |
| 1637   | 0:13:42 | 891  | G       | g++0x    | OK                  | N/A         | [View](http://opentrains.snarknews.info/~ejudge/team.cgi?SID=55539cd5404a04a6&run_id=1637&action=36) | N/A         |

半小时以内，在读题意义下，做出两道签到，不算太慢

然后读题，跟榜发现J题有人过，几何题，没费什么时间我们就搞出了做法，学姐稍加思索细节，然后去写；主要可能实现除了点细节差错，稍微慢了一点，到这里差不多一个半小时

学姐想H，突然发现似曾相识却不会；滨滨在想E，没突破；然后中间不知道为什么上个厕所学姐H就会了，滨滨出去。

我中间主要在想A，到此已经基本想清楚主要部分，等待讨论；我去看了E,H,I快速想了几分钟。

滨滨回来，先交流A，觉得基本OK，传递给学姐，马上开始写；稍微遇到了些坎坷，具体什么问题没交流，但是10分钟以内调还好，这是一道需要讨论清楚的一些偏细节的线段树。

然后我们讨论E，抛弃了自动机的想法，我们突然发现普通的dp更有优势，可以矩阵优化；进一步就想到了一个用到线段树的nm^3做法；觉得可能不够，而且常数大；我们注意到区间长度是不变的，这样就相当于划窗问题，上次有做过一道双栈的题目，改用双栈做法，复杂度认为还是nm^3的；然后这题给了滨滨思考进一步优化，如果不能优化就直接写了。当时知道这个矩阵是稀疏的，具体怎么个情况还不太清楚。我去想B，有点点想法。

滨滨没找到优化，上去写，我把矩阵推清楚了，矩阵就对角线两斜行有元素；后面主要时间都在调E了，大概搞了三十几分钟找到错误在矩阵乘法写错，E过了。

中途我和学姐讨论B，这是一道构造题，沿着我之前的思路，开始连猜带蒙冒进的乱搞了，中途尝试几次都有问题。大概还有十几分钟的时候，我想到了个事实上可以过的做法，但是当时不知道是不是对的，无法证明，也觉得不太靠谱，而且时间不太够了，就直接没交流了，这题弃了。最后十分钟，相当于全力在E上了。

其次，中途我和学姐有在想I，她给出了个基本的贪心思想，我check主要方向是没错的，她叫我想实现，我觉得并不成熟，而且不容易做。当时，这个题目有个关键的要点没有捕捉到，导致搞了很复杂，没走进去。



场下发现，我们E的写法复杂度是正确的，因为矩阵里面有O(m)个非0元素。这个属于一个复杂度估计上的失误吧，可能也和但是只认识到这是个稀疏矩阵，却还没有详细的写出来写清楚，所以看得不够通透。



最主要的问题在于，B不会，本质的讲，这种构造找到做法之后，因为不能证明，搞不清楚，就只能不断冲，那时没时间了。我觉得要么就想办法大家一起讨论，各出力量；要么，尤其在客观条件不允许的情况下，拼尽全力，不断冲。大范围提高构造能力，未必很现实，也未必有效。

 

至于I题，没做出来，我觉得本质上还是时间不太够吧，可能多些时间讨论，会更有希望；但这题写起来并不容易，考场上不见得容易通过。 