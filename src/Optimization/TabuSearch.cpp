class TabuList {

};

void tabu_search(Activities& a, Rooms& r, Students& s, Teachers& t) {
    a.update_blame_all(r, t, s);
	int current_score = a.objective();

    while (true) {
        
    }
}