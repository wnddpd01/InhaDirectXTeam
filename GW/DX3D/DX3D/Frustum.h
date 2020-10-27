#pragma once
class CFrustum
{
public:
	CFrustum();
	~CFrustum();

private:

	
	
public:

};

/*
D3DXVec3Unproject(vertex1, vertex2, NULL, proj, view, NULL); 공간상 뷰에 위치에서 바라보는 절두체의 면을 생성

D3DXPlaneFromPoints(OUT 면 plane , v1, v2, v3);

D3DXPlaneDotCoord(plane, vC);
값이 양수인가 음수인가 판별 (앞에있는가 뒤에있는가) 이걸로 그릴지 말지 판별 => 양수면 절두체 내부 포함
*/