#pragma once
long __stdcall DrawMenu(LPDIRECT3DDEVICE9 pDevice)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show = !show;
	}

	if (show) {
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		if (ImGui::Begin(_xor_("wchorescrack github").c_str(), &show, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_AlwaysAutoResize))
		{
			

			ImGui::Checkbox("Legit Recoil", &Settings::Visual::lRecoil);
			ImGui::Checkbox("Chams", &Settings::Visual::nxchams);
			ImGui::Checkbox("Nametags", &Settings::Visual::nametag);
			ImGui::SliderInt("Speed Hack", &Settings::Visual::speed, 0, 10);
			ImGui::SliderInt("Super Jump", &Settings::Visual::jump, 0, 10);
			ImGui::Checkbox("HP Hack", &Settings::Visual::HpHack);
			ImGui::Checkbox("FPS", &Settings::Visual::fps);


			

			
		}

		ImGui::End();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	Routine::Handle(pDevice);
	return HooksD3D::EndScene(pDevice);
}