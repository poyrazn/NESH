//
//  nesh.h
//  NESH
//
//  Created by Nehir Poyraz on 23.12.2017.
//  Copyright © 2017 Nehir Poyraz. All rights reserved.
//

#ifndef nesh_h
#define nesh_h
#include <stdio.h>
#define bool int
#define true 1
#define false 0
int nesh_help(char **args);
int nesh_nman(char **args);
int nesh_whereami(char **args);
int nesh_cd(char **args);
int nesh_nsort(char **args);
int nesh_play(char **args);
int nesh_convert(char **args);
int nesh_exit(char **args);
int nman_help(char **args);
int nman_nman(char **args);
int nman_whereami(char **args);
int nman_cd(char **args);
int nman_nsort(char **args);
int nman_play(char **args);
int nman_convert(char **args);
int nman_exit(char **args);
int nesh_launch(char **args);
char *nesh_read_line(void);
char **nesh_split_line(char *line);
bool isWord (char *token);
bool isPipe (char *token);
void nesh_loop(void);
#endif /* nesh_h */
