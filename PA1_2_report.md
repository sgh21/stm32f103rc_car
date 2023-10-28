## 解题思路和算法原理
### 解题思路
+ 题目主要分为两步走，一部分是通过给定的x轴和y轴正半轴上的n个点，获得n条 _平行不相交_ 的线段。
+ 另一部分是，判断每次选取的 _P(Px,Py)点与n条线段有几个交点_
### 算法原理
1. n条不相交线段的确定：  
    + 将输入的n个坐标分别存入 _x[n]_ , _y[n]_ 中,为保证线段不相交，需要到n各坐标依次进行 _排序_ ，然后一一匹配即可。
    + 数据的规模是 $1-200000$，限时1s，CPU运行效率是GHz,因此，排序的时间复杂度应该为 $nlogn$ ,故采用归并排序算法。
2. m次询问交点计算：
    + 由于P点与原点相连，因此在P左下方的所有区域内的直线都会与OP相交。所以，只需要考虑P在哪两条直线之间相交。
    + 判断P和直线的位置关系采用 ${x\over a}+{y\over b}$ 和1的大小关系，考虑到数据全是int类型，因此将上式改写为整式， ${b*x+a*y}$ 和 $a*b$ 的关系。
    + 同样考虑到时间因素，关系判断的迭代算法采用二分查找，时间复杂度为 $mlogn$ 。实现思路和普通的二分查找基本一致，每次将区间二分，通过比较P和 $mid$ 的位置关系确定下次二分的区间，最多 $logn$ 次确定P点的位置。
3. 具体的代码实现：
    + 归并排序实现：  
    ``` cpp
    void merge(int s, int mid, int e, LI*data) 
    {
        int left_size = mid - s + 1;
        int right_size = e - mid;
        LI* ptr_left = data + s;
        LI* ptr_right = data + mid+1;
        LI* copy = new LI[left_size];
        for (int i = 0; i < left_size; i++) {
            copy[i] = *(ptr_left + i);
        }
        //开始归并
        int i=0,j = 0, k = 0;
        while((j<left_size)&&(k<right_size)){
            ptr_left[i++] = (copy[j] <= ptr_right[k]) ? copy[j++] : ptr_right[k++];
        }
        while (j < left_size) {
            ptr_left[i++] = copy[j++];
        }
        delete []copy;
    }

    void merge_sort(int s,int e, LI*data) 
    {
	    if (s >= e)return;
	    int mid = (s + e) / 2;
	    //递归划分
	    merge_sort(s, mid, data);
	    merge_sort(mid + 1, e, data);
	    //归并
	    merge(s, mid, e, data);
    }
    ```
    + 点的位置二分查找实现：
    ```cpp
    int  point_binSearch(LI* x, LI* y, LI* point, int s, int e) 
    {
        while (s < e) {
            //二分
            int mid = (s + e) / 2;
            //比较和查找
            if (point[0] * y[mid] + point[1] * x[mid] < y[mid] * x[mid]) {
                e = mid;
            }
            else if (point[0] * y[mid] + point[1] * x[mid] == y[mid] * x[mid]) {
                return mid + 1;
            }
            else {
                s = mid+1;
            }
        }
        return s;
    }
    ```
## 遇到的问题和方法
### 遇到的一些问题
+ 在确定点的位置时，起始未考虑P点和所有线段相交的情况（P点在所有线段的右上方）。起始的查找区间是 $0-n-1$ ,但由于 $int$ 取整是下取整，所以最后的相交线段数不可能为 $n$ ，导致程序出现错误。
+ 确定点的位置，未考虑点在某条直线上的情况，将其与在直线左下一同考虑，导致如果该直线为 $mid$ 时，最终结果 $s$ 停在 $mid$ 与正确结果差 1。
+ 在大规模测试时候，出现程序超时，但是算法的时间复杂度没有问题。
### 解决方案
+ 调整起始查找区间为 $0-n$ 由于 $int$ 取整结果不可能为 $n$ 因此不存在访问越界的问题。同时，如果P在所有直线之外，$s$ 最终停在 $n$ ，结果正确。
+ 单独考虑点在某一条直线上的情况，如果找到这条直线，直接返回 $mid+1$ 。
+ 最终发现，由于 _cin_ 为了防止输入和输出混乱，将输入输出流和 _scanf_ 做了同步，因此执行效率比较低，最终我将输入用 _scanf_ 实现，解决了程序超时的问题。
### 问题排查
+ 在问题排查时我主要结合了，在纸上的逻辑推演，在给定规模的情况下，讨论P的落点和结果；单步调试，通过查看过程中的输入和输出与结果的差异，来找到问题所在。
### 参考资料
+ 主要参考了，尹霞老师课上的PPT，复习和重写了归并排序和二分查找，同时还参考了CSDN上一些博主的博客，汲取了一些简单语法和读写操作的实现。
+ 同时，我还请教了何思晓同学 _cin_ 和 _scanf_ 的区别，并且在网上查阅资料进行了深入学习。
## 时间和空间复杂度估算
### 时间复杂度
+ 本程序的算法主要为归并排序和二分查找，因此时间复杂度公式为 ${T(n)=2*nlog(n)+m*log(n)=O(max(n,m)*log(n))}$ 
### 空间复杂度
+ 本程序的主要存储为递归深度 $log(n)$ 的栈空间，以及存储两个坐标用的数组，因此空间复杂度为 $S(n)=log(n)+2*n=O(n)$