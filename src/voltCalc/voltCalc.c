#include "voltCalc.h"

uchar slidV[5] = {0, 0, 0, 0, 0};
uchar weight[5] = {1, 2, 4, 8, 16};
uchar debnum = 0;

/// @brief 平均值滤波
/// @return 滤波后模拟量数值
uchar avgFilt()
{
    uchar V[5];
    int num = 0;
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        delay_nms(50);
        V[i] = getVolt();
    }
    for (i = 0; i < 5; i++)
    {
        num += V[i];
    }
    return ((uchar)(num / 5));
}

/// @brief 滑动平均滤波
/// @return 滤波后模拟量数值
uchar slideavgFilt()
{
    static uchar p = 0;
    int num = 0;
    int i;
    p++;
    if (p > 4)
    {
        p = 0;
    }
    slidV[p] = getVolt();
    for (i = 0; i < 5; i++)
    {
        num += slidV[i];
    }
    return ((uchar)(num / 5));
}

/// @brief 限速滤波
/// @return 滤波后模拟量数值
uchar speedFilt()
{
    uchar V[3];
    V[0] = getVolt();
    V[1] = getVolt();
    if (abs(V[0] - V[1]) <= DV)
    {
        return V[1];
    }
    else
    {
        V[2] = getVolt();
        if (abs(V[1] - V[2]) <= DV)
        {
            return V[2];
        }
        else
        {
            return ((V[1] + V[2]) / 2);
        }
    }
}

/// @brief 限幅滤波
/// @return 滤波后模拟量数值
uchar amplimtFilt()
{
    uchar tmp = getVolt();
    if (abs(volt - tmp) < LV)
    {
        return tmp;
    }
    else
    {
        return volt;
    }
}

/// @brief 中位数滤波
/// @return 滤波后模拟量数值
uchar midFilt()
{
    uchar V[5];
    uchar i, j;
    uchar tmp = 0;
    for (i = 0; i < 5; i++)
    {
        V[i] = getVolt();
    }
    for (i = 1; i < 5; i++)
    {
        for (j = 0; j < 5 - i; j++)
        {
            if (V[j] > V[j + 1])
            {
                tmp = V[j];
                V[j] = V[j + 1];
                V[j + 1] = tmp;
            }
        }
    }
    return V[2];
}

/// @brief 中位平均滤波
/// @return 滤波后模拟量数值
uchar midavgFilt()
{
    uchar V[5];
    uchar i, j;
    uchar tmp = 0;
    int num = 0;
    for (i = 0; i < 5; i++)
    {
        V[i] = getVolt();
    }
    for (i = 1; i < 5; i++)
    {
        for (j = 0; j < 5 - i; j++)
        {
            if (V[j] > V[j + 1])
            {
                tmp = V[j];
                V[j] = V[j + 1];
                V[j + 1] = tmp;
            }
        }
    }
    num = (V[1] + V[2] + V[3]);
    return ((uchar)(num / 3));
}

/// @brief 限幅平均滤波
/// @return 滤波后模拟量数值
uchar limtvgFilt()
{
    uchar V[5];
    int num = 0;
    int i = 0;
    V[0] = volt;
    for (i = 1; i < 5; i++)
    {
        V[i] = getVolt();
        if (abs(V[i] - V[i - 1]) > LV)
        {
            V[i] = V[i - 1];
        }
    }
    for (i = 0; i < 5; i++)
    {
        num += V[i];
    }
    return ((uchar)(num / 5));
}

/// @brief 一阶滞后滤波
/// @return 滤波后模拟量数值
uchar onlastFilt()
{
    return ((1 - LASTA) * volt + LASTA * getVolt());
}

/// @brief 加权递推滤波
/// @return 滤波后模拟量数值
uchar weislidFlit()
{
    static uchar p = 0;
    int num = 0;
    int i;
    slidV[p] = getVolt();
    p++;
    if (p > 4)
    {
        p = 0;
    }
    for (i = 0; i < 5; i++)
    {
        num += weight[i] * (int)slidV[p];
        p++;
        if (p > 4)
        {
            p = 0;
        }
    }
    return ((uchar)(num / 31));
}

/// @brief 消抖滤波
/// @return 滤波后模拟量数值
uchar debFilt()
{
    uchar tmp = getVolt();
    if (volt == tmp)
    {
        debnum = 0;
    }
    else
    {
        debnum++;
    }
    if (debnum > MAXDEB)
    {
        debnum = 0;
        return tmp;
    }
    else
    {
        return volt;
    }
}

/// @brief 限幅消抖滤波
/// @return 滤波后模拟量数值
uchar debavgFilt()
{
    uchar tmp = getVolt();
    if (volt == tmp)
    {
        debnum = 0;
    }
    else
    {
        if (abs(volt - tmp) < LV)
        {
            debnum++;
        }
    }
    if (debnum > MAXDEB)
    {
        debnum = 0;
        return tmp;
    }
    else
    {
        return volt;
    }
}

/// @brief 用于快速切换滤波方式的函数指针数组
uchar (*filtFuns[11])() =
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