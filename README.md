# 计算机控制课程设计

## 简要说明

本工程为基于C52系列单片机开发的数模转换课程设计

## 支持的滤波功能

滤波功能由函数指针数组提供,故存在由外部切换滤波方式的接口。
同样可直接调用函数本身。

~~~C
uchar (*filtFuns[11]) () = 
{
avgFilt,
slideavgFilt,
speedFilt,
amplimtFilt,
midFilt,
midavgFilt,
limtvgFilt,
onlastFilt,
weislidFlit,
debFilt,
debavgFilt,
};
~~~

功能依次为：
|序号|功能|函数名|
|---|---|---|
|0|平均值滤波|uchar avgFilt()|
|1|滑动平均滤波|uchar slideavgFilt()|
|2|限速滤波|uchar speedFilt()|
|3|限幅滤波|uchar amplimtFilt()|
|4|中位数滤波|uchar midFilt()|
|5|中位平均滤波|uchar midavgFilt()|
|6|限幅平均滤波|uchar limtvgFilt()|
|7|一阶滞后滤波|uchar onlastFilt()|
|8|加权递推|uchar weislidFlit()|
|9|消抖滤波|uchar debFilt()|
|10|限幅消抖滤波|uchar debavgFilt()|
