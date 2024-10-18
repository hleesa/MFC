
// GLIMDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GLIM.h"
#include "GLIMDlg.h"
#include "afxdialogex.h"

#include <random>
#include <iostream>
#include <afx.h>       
#include <windows.h>  
#include <Shlwapi.h>  
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGLIMDlg 대화 상자



CGLIMDlg::CGLIMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_DIALOG, pParent)
	, m_nX1(640)
	, m_nY1(480)
	, m_nX2(0)
	, m_nY2(0)
	, m_nDx(0)
	, m_nDy(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGLIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_nX1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_nY1);
	DDX_Text(pDX, IDC_EDIT_X2, m_nX2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_nY2);
}

BEGIN_MESSAGE_MAP(CGLIMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGLIMDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGLIMDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGLIMDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CGLIMDlg 메시지 처리기

BOOL CGLIMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGLIMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGLIMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGLIMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGLIMDlg::OnBnClickedBtnDraw()
{
	constexpr int nWidth = 640;
	constexpr int nHeight = 480;
	constexpr int nBpp = 8;

	if (!m_image.IsNull()) {
		m_image.Destroy();
	}
	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; ++i) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	const int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	m_nRadius = generateRandomNumber(1, m_image.GetHeight() / 2);
	m_nColor = generateRandomNumber(100, 255);
	memset(fm, 0x0, sizeof(unsigned char) * nWidth * nHeight);
	UpdateData(TRUE);
	if (m_nX2 != m_nX1) {
		m_nDx = std::ceil(1.0 / std::abs((double)(m_nX2 - m_nX1)));
		if (m_nX2 < m_nX1) {
			m_nDx = -m_nDx;
		}
	}
	if (m_nY2 != m_nY1) {
		m_nDy = std::ceil(1.0 / std::abs((double)(m_nY2 - m_nY1)));
		if (m_nY2 < m_nY1) {
			m_nDy = -m_nDy;
		}
	}
	drawCircle(fm, m_nX1, m_nY1, m_nColor);
	UpdateDisplay();
}

void CGLIMDlg::UpdateDisplay() {
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CGLIMDlg::drawCircle(unsigned char* fm, int centerX, int centerY, int nColor) {
	const int nPitch = m_image.GetPitch();
	const int radiusSquared = m_nRadius * m_nRadius;

	for (int dy = -m_nRadius; dy <= m_nRadius; ++dy) {
		for (int dx = -m_nRadius; dx <= m_nRadius; ++dx) {
			int distanceSquared = dx * dx + dy * dy;

			if (distanceSquared <= radiusSquared) {
				int posX = centerX + dx;
				int posY = centerY + dy;

				if (validaImgPos(posX, posY)) {
					fm[posY * nPitch + posX] = nColor;
				}
			}
		}
	}
}

int CGLIMDlg::generateRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

void CGLIMDlg::moveCircle(int dx, int dy) {
	unsigned char* fm = (unsigned char*)m_image.GetBits();
 
	std::cout << m_nX1 << ", " << m_nY1 << "\n";
	drawCircle(fm, m_nX1, m_nY1, 0x0);
	m_nX1 += dx;
	m_nY1 += dy;
	drawCircle(fm, m_nX1, m_nY1, m_nColor);
	UpdateDisplay();
}

BOOL CGLIMDlg::validaImgPos(int x, int y) {
	const int nWidth = m_image.GetWidth();
	const int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);
	return rect.PtInRect(CPoint(x, y));
}

void CGLIMDlg::OnBnClickedBtnAction()
{
	if (m_image.IsNull()) {
		AfxMessageBox(_T("먼저 Draw 버튼을 클릭해 주세요."));
		return;
	}
	while (m_nX1 != m_nX2 || m_nY1 != m_nY2) {
		int dx = (m_nX1 != m_nX2) ? m_nDx : 0;
		int dy = (m_nY1 != m_nY2) ? m_nDy : 0;

		moveCircle(dx, dy);
		SaveImageAsBMP();
	}
}

void CGLIMDlg::SaveImageAsBMP()
{
	TCHAR szPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strPath(szPath);
	int pos = strPath.ReverseFind(_T('\\'));
	if (pos != -1) {
		strPath = strPath.Left(pos + 1); 
	}

	CString imageFolder = strPath + _T("image\\");

	if (!PathIsDirectory(imageFolder)) {
		if (!CreateDirectory(imageFolder, NULL)) {
			DWORD error = GetLastError();
			CString errorMessage;
			errorMessage.Format(_T("이미지 폴더를 생성하는 데 실패했습니다. 오류 코드: %d"), error);
			AfxMessageBox(errorMessage);
			return;
		}
	}

	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);

	CString fileName;
	fileName.Format(_T("image_%04d%02d%02d_%02d%02d%02d.bmp"),
		localTime.tm_year + 1900, localTime.tm_mon + 1, localTime.tm_mday,
		localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

	CString fullFilePath = imageFolder + fileName;

	HRESULT hResult = m_image.Save(fullFilePath, Gdiplus::ImageFormatBMP);  
	if (FAILED(hResult)) {
		AfxMessageBox(_T("이미지 저장에 실패했습니다."));
	}
}

void CGLIMDlg::OnBnClickedBtnOpen() {
	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST, _T("이미지 파일 (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg|모든 파일 (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();

		if (!m_image.IsNull()) {
			m_image.Destroy();  
		}

		HRESULT hResult = m_image.Load(filePath);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("이미지를 불러오지 못했습니다."));
			return;
		}

		FindCircleCenterAndDraw();
	}
}

void CGLIMDlg::FindCircleCenterAndDraw() {
	const int width = m_image.GetWidth();
	const int height = m_image.GetHeight();
	const int pitch = m_image.GetPitch();
	unsigned char* pixels = (unsigned char*)m_image.GetBits();

	int sumX = 0, sumY = 0, count = 0;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			unsigned char pixelValue = pixels[y * pitch + x];

			if (pixelValue >= 100 && pixelValue <= 255) {
				sumX += x;
				sumY += y;
				count++;
			}
		}
	}

	if (count > 0) {
		int centerX = sumX / count;
		int centerY = sumY / count;
		DrawXAndShowCoords(centerX, centerY); 
	}
	else {
		AfxMessageBox(_T("원을 찾을 수 없습니다."));
	}
}

void CGLIMDlg::DrawXAndShowCoords(int centerX, int centerY) {
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);

	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);

	dc.MoveTo(centerX - 10, centerY - 10);
	dc.LineTo(centerX + 10, centerY + 10);
	dc.MoveTo(centerX - 10, centerY + 10);
	dc.LineTo(centerX + 10, centerY - 10);

	dc.SelectObject(pOldPen);

	CString strCoord;
	strCoord.Format(_T("X: %d, Y: %d"), centerX, centerY);
	dc.TextOutW(centerX + 15, centerY + 15, strCoord);
}
