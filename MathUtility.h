#pragma once

class MathUtility
{
public:

    static D3DXVECTOR2 DegreeToVector2(float degree)
    {
        return RadianToVector2(D3DXToRadian(90.0f - degree));
    }

    static D3DXVECTOR2 RadianToVector2(float radian)
    {
        return D3DXVECTOR2(cosf(radian), sinf(radian));
    }

};