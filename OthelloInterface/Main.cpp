#include <Siv3D.hpp>

using Table = Grid<char>;

class GameEngine {
private:

	bool isPut(const Table& table, const Point& pos) const {



		return false;
	}

public:

	Grid<bool> getPutTable(const Table& table) const {

		Grid<bool> putTable(table.size());

		for (const auto& p : step(table.size()))
		{
			putTable[p] = isPut(table, p);
		}

		return putTable;
	}

};

class Inputer {
private:

	int size;

	int startTime;
	int lifeTime;
	char color;

	Table table;
	Grid<bool> putTable;

	Point clickPos;

	Stopwatch sw;
	GameEngine engine;

	const int CellSize = 32;

	const Point TablePoint{ 0,0 };

	void drawTable(const Point& pos) const {

		for (const auto& p : step({ size,size }))
		{
			Rect cell(pos + p*CellSize, CellSize, CellSize);

			cell.draw(Palette::Lightgreen);
			cell.drawFrame(0, 1, Palette::Black);

			Circle stone(cell.center, CellSize / 2 - 2);

			switch (table[p])
			{
			case '-': break;
			case 'b':
				stone.draw(Palette::Black);
				break;
			case 'w':
				stone.draw(Palette::White);
				break;
			default:
				break;
			}

		}

	}

	void drawTimer(const Point& pos) const {

		Rect timer(pos, 160, 120);

		timer.draw(Palette::Gray);

		PutText(Milliseconds(lifeTime) - sw.elapsed()).from(timer.pos + Vec2{ 4, 4 });

	}

public:

	Inputer() {

		std::cin >> size >> startTime >> color;
		lifeTime = startTime;
		table.resize(size, size);
	}

	bool input() {

		std::cin >> lifeTime;

		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				std::cin >> table[y][x];
			}
			std::cin.ignore();
		}

		std::string end;

		std::cin >> end;
		std::cin.ignore();

		sw.restart();

		return end == "END";
	}

	void setup() {

		putTable = engine.getPutTable(table);

	}

	bool update() {

		if (Input::MouseL.released)
		{
			const auto& pos = Mouse::Pos() / CellSize;

			if (table.inBounds(pos))
			{
				clickPos = pos;
				return true;
			}
		}

		return false;
	}

	void draw() const {

		drawTable(TablePoint);

		drawTimer({ TablePoint.x + CellSize * size,0 });

	}

	Point getPos() const { return clickPos; }

};

void Main()
{
	//Console::Open();

	std::cout << "ao1415" << std::endl;

	std::cout.flush();

	Inputer inputer;

	while (System::Update() && inputer.input())
	{
		inputer.setup();

		bool input = false;
		while (!input && System::Update())
		{
			input = inputer.update();

			inputer.draw();
		}

		const auto pos = inputer.getPos();

		std::cout << pos.x << " " << pos.y << std::endl;
		std::cout.flush();
	}

	//Console::Close();
}
