#include "func.h"

#define N 20000000
//两个进程各加1千万
int main()
{
			int shmid;
				shmid=shmget((key_t)1234,4096,IPC_CREAT|0600);
					if(-1==shmid)
								{
												perror("shmget");
														return -1;
															}
						printf("shmid=%d\n",shmid);
							int sem_id;
								sem_id=semget(1234,1,IPC_CREAT|0600);//创建信号量集合
									if(-1==sem_id)
												{
																perror("semget");
																		return -1;
																			}
										int ret;
											ret=semctl(sem_id,0,SETVAL,1);//初始化信号量的值
												if(-1==ret)
															{
																			perror("semctl");
																					return -1;
																						}
													int *p;
														p=(int*)shmat(shmid,NULL,0);
															if((int*)-1==p)
																		{
																						perror("shmat");
																								return -1;
																									}
																p[0]=0;
																	int i=0;
																		struct sembuf sopp,sopv;
																			bzero(&sopp,sizeof(sopp));
																				bzero(&sopv,sizeof(sopv));
																					sopp.sem_num=0;
																						sopp.sem_op=-1;
																							sopp.sem_flg=SEM_UNDO;
																								sopv.sem_num=0;
																									sopv.sem_op=1;
																										sopv.sem_flg=SEM_UNDO;
																											time_t start,end;
																												start=time(NULL);
																													if(!fork())
																																{
																																				for(i=0;i<N;i++)
																																								{
																																													semop(sem_id,&sopp,1);
																																																p[0]=p[0]+1;
																																																			semop(sem_id,&sopv,1);
																																																					}
																																						return 0;
																																							}else{
																																											for(i=0;i<N;i++)
																																															{
																																																				semop(sem_id,&sopp,1);
																																																							p[0]=p[0]+1;
																																																										semop(sem_id,&sopv,1);
																																																												}
																																													wait(NULL);
																																															end=time(NULL);
																																																	printf("p[0]=%d,total=%ld\n",p[0],end-start);
																																																			return 0;
																																																				}
																														return 0;
}

