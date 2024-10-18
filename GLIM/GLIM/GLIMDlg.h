
// GLIMDlg.h: 헤더 파일
//

#pragma once
#include <functional>

// CGLIMDlg 대화 상자
class CGLIMDlg : public CDialogEx
{
// 생성입니다.
private:
	CImage m_image;
	BOOL validaImgPos(int x, int y);
public:
	CGLIMDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	int m_nX1;
	int m_nY1;
	int m_nX2;
	int m_nY2;

	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();

private:
	int m_nRadius;
	int m_nColor;
	int m_nDx;
	int m_nDy;

	void UpdateDisplay();
	void drawCircle(unsigned char* fm, int x1, int y1, int nColor);
	int generateRandomNumber(int min, int max);
	void moveCircle(int dx, int dy);
	void SaveImageAsBMP();
	void FindCircleCenterAndDraw();
	void DrawXAndShowCoords(int centerX, int centerY);
};
