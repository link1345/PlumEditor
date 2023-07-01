#include "stdafx.h"

#include "DearImGuiAddon.hpp"
#include "imgui_impl_s3d.h"

#include "nodes.h"

#include "top.h"


/*
void Main()
{
	// ------------------------------------------------------

	Addon::Register<DearImGuiAddon>(U"ImGui");

	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });


	// 絵文字からテクスチャを作成する | Create a texture from an emoji
	const Texture emoji{ U"🦖"_emoji };

	// 太文字のフォントを作成する | Create a bold font with MSDF method
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// テキストに含まれる絵文字のためのフォントを作成し、font に追加する | Create a font for emojis in text and add it to font as a fallback
	const Font emojiFont{ 48, Typeface::ColorEmoji };
	font.addFallback(emojiFont);

	// ボタンを押した回数 | Number of button presses
	int32 count = 0;

	// チェックボックスの状態 | Checkbox state
	bool checked = false;

	std::unordered_map < ImTextureID, Texture, decltype([](ImTextureID id) { return reinterpret_cast<size_t>(id); }) > textureDic;

	RenderTexture renderTexture{ 200, 200, Palette::White };

	ImGui_Impls3d_RegisterTexture(renderTexture); // これでimguiで描画しますよ～とs3dに告知します

	ImGui::ImGuiNodes node;

#ifdef _DEBUG
	node.isDebug = true;
#else
	node.isDebug = false;
#endif // DEBUG

	bool* p_open = NULL;

	Script test_script{ U"hello.as" };

	for (int i = 0; i < test_script.GetEngine()->GetGlobalFunctionCount(); i++) {
		auto func = test_script.GetEngine()->GetGlobalFunctionByIndex(i);

		auto decl = func->GetDeclaration(true, true, true);
		Logger << U"decl : " << Unicode::Widen(decl);
	}


	std::vector<AngelScript::asIScriptFunction*> remove_obj;
	for (int i = 0; i < test_script.GetEngine()->GetObjectTypeCount(); i++) {
		auto obj = test_script.GetEngine()->GetObjectTypeByIndex(i);
		Logger << U"objName : " << Unicode::Widen(obj->GetName());

		for (int j = 0; j < obj->GetChildFuncdefCount(); j++) {
			auto obj_module_func = obj->GetChildFuncdef(j);

			Logger << U"obj_func name : " << Unicode::Widen(obj_module_func->GetName());
		}

		auto obj_module = obj->GetModule();
		if (obj_module != NULL) {
			Logger << U"Hit";
		}

		for (int j = 0; j < obj->GetMethodCount(); j++) {
			auto obj_module_func = obj->GetMethodByIndex(j);

			Logger << U"obj_method name : " << Unicode::Widen(obj_module_func->GetName());


			remove_obj.push_back(obj_module_func);

			auto obj_medthod_module = obj_module_func->GetModule();

			if (NULL != obj_module_func->GetModule()) {
				Logger << U"Hit";
				auto count_medthod_func = obj_module_func->GetModule()->GetFunctionCount();
			}
		}
	}

	//test_script.reload();

	int module_count = test_script.GetEngine()->GetGlobalFunctionCount();

	auto script_func = test_script.getFunction<void()>(U"Main");

	//test_script.GetEngine()->GetGlobalFunctionByDecl("Main")->Release();

	//test_script.reload();

	while (System::Update() && test_script.compiled())
	{

		if (SimpleGUI::Button(U"Push", Vec2{ 520, 370 }, 120, (checked == false)))
		{

		}
		StringView text_view{};

		String exception;

		script_func.tryCall(exception);
		if (exception)
		{
			Print << U"[script exception] " << exception;
		}

		//test_script.run();
		//bool error = script.compiled();

		//if (!error) {
		//	Circle(Cursor::Pos(), 40).draw(ColorF(0, 0, 1, 0.5));
		//}

		// ---------------------

		ImGui::ShowDemoWindow();

		// -----------------

		//if (ImGui::Begin("nodes", p_open, ImGuiWindowFlags_NoMove)) {
		//	node.Update();
		//	node.ProcessContextMenu();
		//	node.ProcessNodes();
		//	ImGui::End();
		//}

		// -----------------


		ImVec2 texturePos;

		if (ImGui::Begin("image")) {
			texturePos = ImGui::GetCursorScreenPos();

			ImGui::Text("pointe");

			//Logger << U"empty : " << (renderTexture.isEmpty() ? U"true" : U"false");

			if (!renderTexture.id().isNull() && !renderTexture.id().isInvalid() && !renderTexture.isEmpty()) {

				//Logger << (renderTexture.width());
				//Logger << (renderTexture.height());

				ImGui::Image(reinterpret_cast<ImTextureID>(renderTexture.id().value()), ImVec2(renderTexture.width(), renderTexture.height()));
			}

		}
		ImGui::End();


		// レンダーテクスチャを白色でクリア
		renderTexture.clear(Palette::White);
		{
			// レンダーターゲットを renderTexture に変更
			const ScopedRenderTarget2D target{ renderTexture };

			Transformer2D t(Mat3x2::Identity(), Mat3x2::Translate(texturePos.x, texturePos.y));

			auto circle = Circle{ 200, 200, 50 };
			emoji.rotated(Scene::Time() * 30_deg).drawAt(100, 100);

			circle.draw(ColorF{ 0.8, 0.9, 1.0 });

			if (circle.mouseOver())
			{
				circle.draw(Palette::Skyblue);
			}
			else
			{
				circle.draw(Palette::Gray);
			}
		}

		// レンダーテクスチャを描画する
		//renderTexture.draw(0, 0);
		//renderTexture.draw(0, 300);
	}

}*/

void Main()
{
	// ------------------------------------------------------
	Addon::Register<DearImGuiAddon>(U"ImGui");

	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });


	auto top = Plum::Top();

	while (System::Update())
	{
		top.Main();

		ImGui::ShowDemoWindow();
	}

}
