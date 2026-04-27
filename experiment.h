#ifndef EXPERIMENT_H
#define EXPERIMENT_H

struct Experiment {
	size_t table_start_capacity;
	int collisions;
};

Experiment experiment(size_t table_start_capacity);

#endif