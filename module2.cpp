#include "module2.h"

#include "resource2.h"
#include "resource3.h"


static INT_PTR CALLBACK Mdule2_1_Processing(HWND hDlg, UINT iMessege, WPARAM wParam, LPARAM)
{
	if (iMessege == WM_COMMAND)
	{
		switch (LOWORD(wParam))
		{
		case IDC_BTN_NEXT:
			EndDialog(hDlg, 1);
			return TRUE;
		case IDC_BTN_CENCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		default: break;
		}
	}
	return FALSE;
}


static INT_PTR CALLBACK Mdule2_2_Processing(HWND hDlg, UINT iMessege, WPARAM wParam, LPARAM)
{
	if (iMessege == WM_COMMAND)
	{
		switch (LOWORD(wParam))
		{
		case IDC_BTN_BACK:
			EndDialog(hDlg, -1);
			return TRUE;
		case IDC_BTN_CENCEL2:
			EndDialog(hDlg, 0);
			return TRUE;
		case IDC_BTN_DONE:
			EndDialog(hDlg, 1);
			return TRUE;
		default: break;
		}
	}
	return FALSE;
}


// Define states for the wizard/module flow
enum ModuleState {
	EXIT = 0,
	STEP_1 = 1,
	STEP_2 = 2
};

// Define standard dialog return values
enum DialogResult {
	BACK = -1,
	CANCEL = 0,
	NEXT_OR_DONE = 1
};

int Func_MODULE2(HWND hWnd)
{
	ModuleState state = STEP_1;

	while (state != EXIT) {
		if (state == STEP_1) {
			int res = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MODULE2_1), hWnd, Mdule2_1_Processing);

			if (res == NEXT_OR_DONE) state = STEP_2;    // Pressed next
			else if (res == CANCEL)  state = EXIT;      // Pressed cancel
			
		}
		else if (state == STEP_2) {
			int res = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MODULE2_2), hWnd, Mdule2_2_Processing);

			if (res == BACK) state = STEP_1;				// Pressed back
			else if (res == NEXT_OR_DONE) state = EXIT;     // Pressed done
			else if (res == CANCEL) state = EXIT;			// Pressed cancel
			
		}
	}

	return 0;
}