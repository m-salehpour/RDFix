// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2015-2017, Intel Corporation */

/*
 * map.c -- common interface for maps
 */
#include <stdlib.h>
#include <stdio.h>
#include <libpmemobj.h>

#include "map.h"



long mapc_counter=0;

#define ABORT_NOT_IMPLEMENTED(mapc, func)\
	if ((mapc)->ops->func == NULL) {\
		fprintf(stderr, "error: '%s'"\
			" function not implemented\n", #func);\
		exit(1);\
	}

/*
 * map_ctx_init -- initialize map context
 */
struct map_ctx *
map_ctx_init(const struct map_ops *ops, PMEMobjpool *pop)
{
	if (!ops)
		return NULL;

	struct map_ctx *mapc = (struct map_ctx *)calloc(1, sizeof(*mapc));

	//mapc_counter+=16;
	if (mapc_counter % 1000000 == 0 || mapc_counter == 10)
		printf("\n sizeof *mapc:%ld \n", ++mapc_counter );
	//mapc_counter+=16;

	if (!mapc)
		return NULL;

	mapc->ops = ops;
	mapc->pop = pop;

	return mapc;
}

/*
 * map_ctx_free -- free map context
 */
void
map_ctx_free(struct map_ctx *mapc)
{
	free(mapc);
}

/*
 * map_create -- create new map
 */
int
map_create(struct map_ctx *mapc, TOID(struct map) *map, void *arg)
{
	ABORT_NOT_IMPLEMENTED(mapc, create);
	return mapc->ops->create(mapc->pop, map, arg);
}

/*
 * map_destroy -- free the map
 */
int
map_destroy(struct map_ctx *mapc, TOID(struct map) *map)
{
	ABORT_NOT_IMPLEMENTED(mapc, destroy);
	return mapc->ops->destroy(mapc->pop, map);
}

/*
 * map_init -- initialize map
 */
int
map_init(struct map_ctx *mapc, TOID(struct map) map)
{
	ABORT_NOT_IMPLEMENTED(mapc, init);
	return mapc->ops->init(mapc->pop, map);
}

/*
 * map_check -- check if persistent object is a valid map object
 */
int
map_check(struct map_ctx *mapc, TOID(struct map) map)
{
	ABORT_NOT_IMPLEMENTED(mapc, check);
	return mapc->ops->check(mapc->pop, map);
}

/*
 * map_insert -- insert key value pair
 */
int
map_insert(struct map_ctx *mapc, TOID(struct map) map,
	uint64_t key, PMEMoid value)
{
	ABORT_NOT_IMPLEMENTED(mapc, insert);
	return mapc->ops->insert(mapc->pop, map, key, value);
}

/*
 * map_insert_new -- allocate and insert key value pair
 */
int
map_insert_new(struct map_ctx *mapc, TOID(struct map) map,
		uint64_t key, size_t size, unsigned type_num,
		void (*constructor)(PMEMobjpool *pop, void *ptr, void *arg),
		void *arg)
{
	ABORT_NOT_IMPLEMENTED(mapc, insert_new);
	return mapc->ops->insert_new(mapc->pop, map, key, size,
			type_num, constructor, arg);
}

/*
 * map_remove -- remove key value pair
 */
PMEMoid
map_remove(struct map_ctx *mapc, TOID(struct map) map, uint64_t key)
{
	ABORT_NOT_IMPLEMENTED(mapc, remove);
	return mapc->ops->remove(mapc->pop, map, key);
}

/*
 * map_remove_free -- remove and free key value pair
 */
int
map_remove_free(struct map_ctx *mapc, TOID(struct map) map, uint64_t key)
{
	ABORT_NOT_IMPLEMENTED(mapc, remove_free);
	return mapc->ops->remove_free(mapc->pop, map, key);
}

/*
 * map_clear -- remove all key value pairs from map
 */
int
map_clear(struct map_ctx *mapc, TOID(struct map) map)
{
	ABORT_NOT_IMPLEMENTED(mapc, clear);
	return mapc->ops->clear(mapc->pop, map);
}

/*
 * map_get -- get value of specified key
 */
PMEMoid
map_get(struct map_ctx *mapc, TOID(struct map) map, uint64_t key)
{
	ABORT_NOT_IMPLEMENTED(mapc, get);
	return mapc->ops->get(mapc->pop, map, key);
}

/*
 * map_lookup -- check if specified key exists in map
 */
int
map_lookup(struct map_ctx *mapc, TOID(struct map) map, uint64_t key)
{
	ABORT_NOT_IMPLEMENTED(mapc, lookup);
	return mapc->ops->lookup(mapc->pop, map, key);
}

/*
 * map_foreach -- iterate through all key value pairs in a map
 */
int
map_foreach(struct map_ctx *mapc, TOID(struct map) map,
		int (*cb)(uint64_t key, PMEMoid value, void *arg),
		void *arg)
{
	ABORT_NOT_IMPLEMENTED(mapc, foreach);
	return mapc->ops->foreach(mapc->pop, map, cb, arg);
}

/*
 * map_is_empty -- check if map is empty
 */
int
map_is_empty(struct map_ctx *mapc, TOID(struct map) map)
{
	ABORT_NOT_IMPLEMENTED(mapc, is_empty);
	return mapc->ops->is_empty(mapc->pop, map);
}

/*
 * map_count -- get number of key value pairs in map
 */
size_t
map_count(struct map_ctx *mapc, TOID(struct map) map)
{
	ABORT_NOT_IMPLEMENTED(mapc, count);
	return mapc->ops->count(mapc->pop, map);
}

/*
 * map_cmd -- execute command specific for map type
 */
int
map_cmd(struct map_ctx *mapc, TOID(struct map) map, unsigned cmd, uint64_t arg)
{
	ABORT_NOT_IMPLEMENTED(mapc, cmd);
	return mapc->ops->cmd(mapc->pop, map, cmd, arg);
}
