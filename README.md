## 华为软件精英挑战赛
### 数据
[HWcode2020-TestData](https://github.com/byl0561/HWcode2020-TestData)

### 时间
鲲鹏测试机上 3512444环 单线程1.2s，初赛线上数据0.37s，多线程时间减半

### 优化“技巧”
1. 4+3搜索，先反向找 i 到 j 的路径i-->m-->n-->j，再正着找i-->a-->b-->c-->j，通过reachable数组来匹配
2. 使用 array 代替 vector 存图，存图的时候按大小反过来存，这样遍历的时候可以不用二分搜索找到比 i 大的节点
3. 存结果的时候也使用二维数组
4. 保存反向路径的时候用两个数组代替unordered_map数据结构（哈希表这个数据结构真的慢）
5. 读数据使用mmap，写结果用memcpy, 比直接用 string += 要快
6. 以上“技巧”比起 “50000” 都是雕虫小技，这种奇淫怪技真的学不会（代码里没有用）

### 复赛
复赛代码写的比较丑，成绩(1963环 9s)也没那么好，就不放上来了。

### 其他队伍方案

[ddd2020](https://github.com/justarandomstring/2020-Huawei-Code-Craft)

[粤港澳复赛A榜第2，全国第12](https://github.com/Buerzhu/CodeCraft2020)

[华为2020软件精英挑战赛复赛代码开源（京津东北赛区1504b，复赛Ａ榜 rank1, B榜无有效成绩)](https://github.com/WavenZ/CodeCraft2020)

[上合赛区初赛rank3，复赛a榜rank4，b榜rank1](https://github.com/HanChaoo/CodeCraft2020)

[热身赛146/944 0.96 西北赛区：初赛 40/975 0.4798 复活赛区：复赛 a榜 26/266 b榜 4](https://github.com/wclever/HuaWeiCodeCraft2020)

[2020华为软挑初赛武长赛区第一，复赛武长赛区A榜第二解决方案](https://github.com/yoghurt-lee/HuaWeiCodeCraft2020)

[2020华为软件精英挑战赛-武长赛区-团队“您吃了么”初赛/复赛代码分享](https://github.com/liuwentao1992/HuaweiCodeCraft-2020)

[2020年华为软件精英挑战赛（复赛A榜）参考代码](https://github.com/RickiZhang/2020HWCodeCraft)