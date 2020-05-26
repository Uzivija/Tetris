#include "pch.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>
#include <string>
#include<iostream>
#include<sstream>

const int columns = 10;
const int row = 20;

int field[row][columns] = { 0 };

const int cell_size = 40;

int figures[7][4][4] =
{
	1,0,0,0,
	1,0,0,0,
	1,0,0,0,
	1,0,0,0,

	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0,

	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,0,0,0,
	1,1,0,0,
	0,0,0,0,

	0,1,0,0,
	0,1,0,0,
	1,1,0,0,
	0,0,0,0,
};


int main()
{

	int shape;
	int x_position;
	int y_position;
	int punkty = 0;
	int x_plus = 100, y_plus = 40;

	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(1200,880, 32), "", sf::Style::Close);
	sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));

	sf::Texture background, background_end,  frame, cells_pic_1, cells_pic_2, cells_pic_3, cells_pic_4, cells_pic_5, cells_pic_6, cells_pic_7;
	background.loadFromFile("images/background_.png");
	background_end.loadFromFile("images/background_end.png");
	cells_pic_1.loadFromFile("images/1.png");
	cells_pic_2.loadFromFile("images/2.png");
	cells_pic_3.loadFromFile("images/3.png");
	cells_pic_4.loadFromFile("images/4.png");
	cells_pic_5.loadFromFile("images/5.png");
	cells_pic_6.loadFromFile("images/6.png");
	cells_pic_7.loadFromFile("images/7.png");

	sf::Font font;
	font.loadFromFile("images/font.ttf");
	sf::Text text;
	
	std::ostringstream PunktyS;
	PunktyS.str("");
	PunktyS << "Zdobyte punkty: " << punkty;
	text.setString(PunktyS.str());



	text.setFont(font);
	text.setCharacterSize(30);
	text.move(700, 500);

	

	const sf::Texture cell_map[] = { cells_pic_1 , cells_pic_2, cells_pic_3, cells_pic_4, cells_pic_5, cells_pic_6, cells_pic_7 };

	// t³o //
	sf::Sprite background_, background_end_;
	background_.setTexture(background);
	background_end_.setTexture(background_end);

	

	auto new_figure = [&]()
	{
		shape = rand() % 7;
		x_position = columns / 2;
		y_position = 0;
		
	};

	new_figure();

	auto check_figure = [&]()
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (figures[shape][y][x] == 0)
					continue;
				 if (x_position + x < 0 || x_position + x >= columns || y_position + y >= row)
					return false;
				 if (field[y_position + y][x_position + x])
					 return false;
			
			}
		}
		return true;
	};

	auto points = [&]()
	{
		PunktyS.str("");
		PunktyS << "Zdobyte punkty: " << punkty;
		text.setString(PunktyS.str());
	};

	auto check_lines = [&]()
	{
		int lines = row - 1;
		for (int line = row - 1; line >= 0; line--)
		{
			int space = 0;
			for (int x = 0; x < columns; x++)
			{
				if (field[line][x])
					space++;
			}
			if (space < columns)
			{
				for (int x = 0; x < columns; x++)
				{
					field[lines][x] = field[line][x];

				}
				lines--;

			}
			else
			{
				punkty = punkty + 100;
				points();
			}
				

		}
	};
	
	auto down = [&]()
	{
		y_position++;
		if (check_figure() == false)
		{
			y_position--;
			for (int y = 0; y < 4; y++)
				for (int x = 0; x < 4; x++)
				{
					if (figures[shape][y][x])
					{
						field[y_position + y][x_position + x] = shape + 1;
					}
				}
			punkty = punkty + 10;
			points();
			check_lines();
			new_figure();
		}
	};

	auto rotate = [&]()
	{
		int rotation[4][4] = { 0 };
		int size = 0;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (figures[shape][y][x])
				{
					size = std::max(std::max(x, y) + 1, size);
				}
			}
		}
		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				if (figures[shape][y][x])
				{
					rotation[x][size-y-1] = figures[shape][y][x];
					figures[shape][y][x] = 0;
				}
			}
		}
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (rotation[y][x])
				{
					figures[shape][y][x]=rotation[y][x];
				}
			}
		}

	};

	while (window.isOpen())
	{
	
		static float time = clock.getElapsedTime().asSeconds();
		if (clock.getElapsedTime().asSeconds() - time >= 0.5)
		{
			time = clock.getElapsedTime().asSeconds();
			down();

		}

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}

			if (evnt.type == evnt.KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::Left)
				{

					x_position--;
					if (check_figure() == false)
					{
						x_position++;
					}
				}
				else if (evnt.key.code == sf::Keyboard::Right)
				{
					x_position++;
					if (check_figure() == false)
					{
						x_position--;
					}
				}
				else if (evnt.key.code == sf::Keyboard::Down)
				{
					down();
				}
				else if (evnt.key.code == sf::Keyboard::Up)
				{
					rotate();
					if (check_figure() == false)
					{
						rotate();
						rotate();
						rotate();
					}
						
				}
				

			}
		}

		window.clear();
		window.draw(background_);
		

		
		auto draw_field = [&]()
		{
			for (int y = 0; y < row; y++)
			{
				for (int x = 0; x < columns; x++)
				{
					if (field[y][x])
					{
						cell.setTexture(&(cell_map[field[y][x]])-1);
						cell.setPosition(sf::Vector2f(x*cell_size, y*cell_size));
						cell.move(x_plus, y_plus);
						window.draw(cell);
					}
				}
			}
		};

		draw_field();


		auto draw_shape = [&]()
		{
			
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					cell.setTexture(&cell_map[shape]);
					if (figures[shape][y][x])
					{
						cell.setPosition(sf::Vector2f((x_position + x)*cell_size, (y_position + y)*cell_size));
						cell.move(x_plus, y_plus);
						window.draw(cell);
					}
					
				
					
				}
			}
		
		
		};

		draw_shape();

		window.draw(text);
		
		window.display();


		int check = 0;
		for (int x = 0; x < columns; x++)
		{
			if (field[0][x])
				check++;
		}
		if (check > 0)
		{
			
			break;
		}
			
	}
	


	while (window.isOpen())
	{
		static float time = clock.getElapsedTime().asSeconds();
		if (clock.getElapsedTime().asSeconds()-time > 6)
		{
			break;
		}

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}
		}

		window.draw(background_end_);

		text.setPosition(450, 445);
		PunktyS.str("");
		PunktyS << "Zdobyte punkty: " << punkty;
		text.setString(PunktyS.str());

		window.draw(text);
		window.display();

	}
	


	return 0;
}