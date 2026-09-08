#include "module1.h"

#include "resource1.h"

static int currentPos = 1;

static INT_PTR CALLBACK Work1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM)
{

	switch (iMessage)
	{
		case WM_INITDIALOG:
		{
			SetScrollRange(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL, 1, 100, TRUE);
			SetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL, currentPos, TRUE);
			return TRUE;
		}
		case WM_HSCROLL:
		{
			currentPos = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL);
			switch (LOWORD(wParam))
			{
				case SB_LINELEFT:		currentPos--;
				case SB_LINERIGHT:		currentPos++;
				case SB_PAGELEFT:		currentPos -= 10;
				case SB_PAGERIGHT:		currentPos += 10;
				case SB_THUMBPOSITION:
				case SB_THUMBTRACK:		currentPos = HIWORD(wParam);
				default: break;
			}

			if (currentPos < 1) currentPos = 1;
			if (currentPos > 100) currentPos = 100;

			SetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL, currentPos, TRUE);
			SetDlgItemInt(hDlg, IDC_STATIC1, currentPos, FALSE);

			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hDlg, currentPos);
					return TRUE;
				case IDCANCEL:
					EndDialog(hDlg, 0);
					return TRUE;

				default: break;
			}
			break;
		}
	default: break;
	}
	return FALSE;
}

int Func_MODULE1(HWND hWnd, int& outValue) {
	int res = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Work1);
	if (res > 0) outValue = res;
	return res;
}