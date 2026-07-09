#include "geneticAlgorithm.h"

AlgorithmState GeneticAlgorithm::getState(){
    return state;
}

Individual GeneticAlgorithm::createIndividual(){
    Individual individ;

    individ.order.resize(cnt_tasks);
    std::iota(individ.order.begin(), individ.order.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(individ.order.begin(), individ.order.end(), g);

    calcDelay(individ);

    return individ;
}

void GeneticAlgorithm::calcDelay(Individual& individ){
    individ.delay = 0;

    int end=0;
    for (int i=0; i < cnt_tasks; i++){
        int j=individ.order[i];
        end += tasks[j].time;

        individ.delay += std::max(0, end-tasks[j].deadline);
    }
}

void GeneticAlgorithm::calcСharacteristic(){
    int sum=0;

    state.bestFitness = INT_MAX;
    state.averageFitness = 0;

    for (int i=0; i < params.populationSize; i++){
        Individual individ = state.population[i];

        state.bestFitness = std::min(state.bestFitness, individ.delay);
        sum += individ.delay;
    }

    state.averageFitness = sum/params.populationSize;
}

void GeneticAlgorithm::run(const std::vector <Task>& t, Parameters& p){
    cnt_tasks = t.size();
    tasks = t;
    params = p;

    for (int i=0; i < params.populationSize; i++)
        state.population.push_back(createIndividual());

    calcСharacteristic();
}

void GeneticAlgorithm::fillOutChild(Individual& parent, Individual& child, int x){
    for (int i=0; i < cnt_tasks; i++){
        if (std::find(child.order.begin(), child.order.end(), parent.order[i]) == child.order.end()){
            while (child.order[x%cnt_tasks] != -1)
                x++;
            child.order[x%cnt_tasks] = parent.order[i];
        }
    }
}

void GeneticAlgorithm::crossover(Individual& parent1, Individual& parent2){
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution <int> dis(0, cnt_tasks-1);

    int x1=dis(g), x2=dis(g);
    if (x2 < x1)
        std::swap(x1, x2);

    Individual child1, child2;
    child1.order.assign(cnt_tasks, -1);
    child2.order.assign(cnt_tasks, -1);

    for (int i=x1; i <= x2; i++){
        child1.order[i] = parent2.order[i];
        child2.order[i] = parent1.order[i];
    }

    fillOutChild(parent1, child1, x2);
    fillOutChild(parent2, child2, x2);

    calcDelay(child1);
    calcDelay(child2);

    new_population.push_back(child1);
    new_population.push_back(child2);
}

void GeneticAlgorithm::mutation(Individual& individ){
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution <int> dis(0, cnt_tasks-1);

    int i=dis(g), j=dis(g);
    if (i == j)
        j = (i+1)%cnt_tasks;

    // std::swap(individ.order[i], individ.order[j]);
    std::reverse(individ.order.begin()+i, individ.order.begin()+j);

    calcDelay(individ);
}

int GeneticAlgorithm::tournament(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution <int> dis(0, params.populationSize-1);

    int x=dis(g), best=x;

    for (int i=1; i < params.tournamentSize; i++){
        x = dis(g);
        if (state.population[x].delay < state.population[best].delay)
            best = x;
    }

    return best;
}

bool cmp(Individual a, Individual b){
    return a.delay < b.delay;
}

void GeneticAlgorithm::step(){
    std::sort(state.population.begin(), state.population.end(), cmp);

    int elite=std::min(params.populationSize/2, params.eliteSize);
    elite += (params.populationSize-elite)%2;

    for (int i=0; i < elite; i++)
        new_population.push_back(state.population[i]);

    for (int i=0; i < (params.populationSize-elite)/2; i++){
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_real_distribution <> dis(0.0, 1.0);

        int p1=tournament(), p2=tournament();
        if (dis(g) < params.Pc)
            crossover(state.population[p1], state.population[p2]);
        else{
            new_population.push_back(state.population[p1]);
            new_population.push_back(state.population[p2]);
        }

        if (dis(g) < params.Pm)
            mutation(new_population[new_population.size()-2]);
        if (dis(g) < params.Pm)
            mutation(new_population[new_population.size()-1]);
    }
    state.population.assign(std::make_move_iterator(new_population.begin()), std::make_move_iterator(new_population.end()));
    new_population.clear();
    new_population.shrink_to_fit();

    calcСharacteristic();
    state.generation++;
}
