
class EntityManager
{
	public:
		EntityManager();
		void addEntity();
		void patrol();
		bool hitting(SDL_Rect rect);
	private:
		std::vector<Player> entities;
};
