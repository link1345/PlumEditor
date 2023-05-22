void Main()
{
	// Draw a red transparent circle that follows the mouse cursor
	Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));

	//while (System::Update())
	//{
	//	Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));
	//}
}