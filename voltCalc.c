#define uchar unsigned char
#include <AT89X52.h>
#include <absacc.h>
#include <math.h>
#include "ADC0808.h"

#define dV 20
#define lastA 0.3
#define maxDeb 5
extern uchar volt;
extern uchar port;

// 平均值滤波
uchar avgFilt()
{
    uchar V[5];
    int num = 0;
    uchar i = 0;
    for (i = 0; i < 5; i++)
    {
        V[i] = getVolt();
    }
    for (i = 0; i < 5; i++)
    {
        num += V[i];
    }
    return (uchar)num / 5;
}

// 滑动平均滤波
uchar slideavgFilt()
{
    static uchar V[5] = {0, 0, 0, 0, 0};
    static tmpPort = 0;
    uchar i = 0;
    int num;
    if (tmpPort != port)
    {
        for (i = 0; i < 5; i++)
        {
            V[i] = 0;
        }
    }
    for (i = 0; i < 4; i++)
    {
        V[i + 1] = V[i];
    }
    V[0] = getVolt();
    for (i = 0; i < 5; i++)
    {
        num += V[i];
    }
    return ((uchar)num / 5);
}

// 限速滤波
uchar speedFilt()
{
    uchar V[3];
    V[0] = getVolt();
    V[1] = getVolt();
    if (abs(V[0] - V[1]) <= dV)
    {
        return V[1];
    }
    else
    {
        V[2] = getVolt();
        if (abs(V[1] - V[2]) <= dV)
        {
            return V[2];
        }
        else
        {
            return (V[2] + V[3]) / 2;
        }
    }
}

// 限幅滤波
uchar amplimtFilt()
{
    uchar tmp = getVolt();
    if (abs(volt - tmp) < 10)
    {
        return tmp;
    }
    else
    {
        return volt;
    }
}

// 中位数滤波
uchar midFilt()
{
    uchar V[5];
    uchar i, j;
    uchar tmp = 0;
    for (i = 0; i < 5; i++)
    {
        V[i] = getVolt();
    }
    for (i = 4; i > 0; i--)
    {
        for (j = 0; j < i; i++)
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

// 中位平均滤波
uchar midavgFilt()
{
    uchar V[5];
    uchar i, j;
    uchar tmp = 0;
    for (i = 0; i < 5; i++)
    {
        V[i] = getVolt();
    }
    for (i = 4; i > 0; i--)
    {
        for (j = 0; j < i; i++)
        {
            if (V[j] > V[j + 1])
            {
                tmp = V[j];
                V[j] = V[j + 1];
                V[j + 1] = tmp;
            }
        }
    }
    return (V[1] + V[2] + V[3]) / 2;
}

// 限幅平均滤波
uchar limtvgFilt()
{
    uchar V[5];
    uchar i;
    uchar tmp = 0;
    uchar num;
    V[0] = volt;
    i = 1;
    while (i > 5)
    {
        if (abs(V[i] - V[i - 1]) < 10)
        {
            V[i] = getVolt();
        }
        else
        {
            V[i] = V[i - 1];
        }
        i++;
    }
    for (i = 0; i < 5; i++)
    {
        num += V[i];
    }
    return ((uchar)num / 5);
}

// 一阶滞后滤波
uchar onlastFilt()
{
    return ((1 - lastA) * volt + lastA * getVolt());
}

//加权递推
uchar weislidFlit()
{
    static uchar V[5] = {0, 0, 0, 0, 0};
    static tmpPort = 0;
    uchar i = 0;
    int num;
    if (tmpPort != port)
    {
        for (i = 0; i < 5; i++)
        {
            V[i] = 0;
        }
    }
    for (i = 0; i < 4; i++)
    {
        V[i + 1] = V[i];
    }
    V[0] = getVolt();
    for (i = 0; i < 5; i++)
    {
        num += (i+1)*V[i];
    }
    return ((uchar)num / (15*5));
}

// 消抖滤波
uchar debFilt()
{
    static uchar i = 0;
    if (volt = getVolt())
    {
        i = 0;
    }
    else
    {
        i++;
    }
    if (i > maxDeb)
    {
        return getVolt();
    }
    else
    {
        return volt;
    }
}
// 限幅消抖滤波
uchar debavgFilt()
{
    static uchar i = 0;
    uchar tmp = getVolt();
    if (volt = tmp)
    {
        i = 0;
    }
    else
    {
        if (abs(volt - tmp) < 10)
        {
            i++;
        }
    }
    if (i > maxDeb)
    {
        return tmp;
    }
    else
    {
        return volt;
    }
}

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