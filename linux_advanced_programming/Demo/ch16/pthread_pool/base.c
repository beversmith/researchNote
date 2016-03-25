#include "pthread_pool.h"

/*
*child_work:the code exec in child thread
*ptr: the ds of thread_node of current thread.
*return :nothing.void * just avoid warning.
*/ 
void *
child_work (void *ptr) 
{
  THREAD_NODE * self = (THREAD_NODE *) ptr;
  
  /*modify the tid attribute the first time exec */ 
  pthread_mutex_lock (&self->mutex);
  
  self->tid = syscall (SYS_gettid);
  
  pthread_mutex_unlock (&self->mutex);
  
  while (1)
  {
    pthread_mutex_lock (&self->mutex);
     
    /*if no task exec,blocked */ 
    if (NULL == self->work)
    {   
      pthread_cond_wait (&self->cond, &self->mutex);
    }
      
      
    self->work->fun (self->work->arg);
      
    self->work->fun = NULL;
    self->work->flag = 0;
    self->work->tid = 0;
    self->work->next = NULL;
      
      
    pthread_mutex_destroy (&self->work->mutex);
      
    free (self->work);
      
    self->work = NULL;
    self->flag = 0;
      
      
        /*
         *get new task from the task_link if not NULL.
         *there no idle thread if there are task to do.
         *if on task ,make self idle and add to the idle queue.
         */ 
    if (task_queue_head->head != NULL)
    {
      TASK_NODE * temp = task_queue_head->head;
          
      task_queue_head->head = task_queue_head->head->next;          
      /*modify self thread attribute */ 
      self->flag = 1;          
    else        
    {          
      /*no task need to exec, add self to idle queue and del from busy queue */ 
      pthread_mutex_unlock (&task_queue_head->mutex);        
          /*self is the last execte thread */ 
      if (pthread_queue_busy->head == self
                && pthread_queue_busy->rear == self)
      {              
          
          /*the first one thread in busy queue */ 
      else if (pthread_queue_busy->head == self
                     && pthread_queue_busy->rear != self)
      {              
              
          
            /*the last one thread in busy queue */ 
      else if (pthread_queue_busy->head != self
                     && pthread_queue_busy->rear == self)            
      {              
           
          
      /*middle one */ 
      else            
      {              
        /*add self to the idle queue */ 
      pthread_mutex_lock (&pthread_queue_idle->mutex);          
        /*now the idle queue is empty */ 
      if (pthread_queue_idle->head == NULL
                || pthread_queue_idle->head == NULL)
      {              
          
      else
      {              
           
        /*signal have idle thread */ 
      pthread_cond_signal (&pthread_queue_idle->cond);    
}
/*
*create thread pool when the system on, and thread number is THREAD_DEF_NUM.
*when init, initial all the thread into a double link queue and all wait fo self->cond. 
*/ 
void
create_pthread_pool (void) 
{
  THREAD_NODE * temp =
    (THREAD_NODE *) malloc (sizeof (THREAD_NODE) * THREAD_DEF_NUM);
  
  {
    printf (" malloc failure\n");
    exit (EXIT_FAILURE);
  }

    /*init as a double link queue */ 
  int i;
  
  {      
      
      
        /*create this thread */ 
    pthread_create (&temp[i].tid, NULL, child_work, (void *) &temp[i]);    
    /*modify the idle thread queue attribute */ 
  pthread_mutex_lock (&pthread_queue_idle->mutex);  

/*
*init_system :init the system glob pointor.
*/ 
void
init_system (void) 
{  
    /*init the pthread_queue_idle */ 
  pthread_queue_idle =
    (PTHREAD_QUEUE_T *) malloc (sizeof (PTHREAD_QUEUE_T));
  
    /*init the pthread_queue_busy */ 
    pthread_queue_busy =
    (PTHREAD_QUEUE_T *) malloc (sizeof (PTHREAD_QUEUE_T));
  
    /*init the task_queue_head */ 
    task_queue_head = (TASK_QUEUE_T *) malloc (sizeof (TASK_QUEUE_T));
  
    /*create thread poll */ 
  create_pthread_pool ();
}

/*
*thread_manager:code exec in manager thread. 
*               block on task_queue_head->cond when no task come.
*               block on pthread_queue_idle->cond when no idle thread 
*ptr:no used ,in order to avoid warning.
*return :nothing.
*/ 

thread_manager (void *ptr) 
{  
  {
    THREAD_NODE * temp_thread = NULL;      
        /*
         *get a new task, and modify the task_queue.
         *if no task block om task_queue_head->cond.
         */ 
    pthread_mutex_lock (&task_queue_head->mutex);      
                             &task_queue_head->mutex);      
      
        /*
         *get a new idle thread, and modify the idle_queue.
         *if no idle thread, block on pthread_queue_idle->cond.
         */ 
        pthread_mutex_lock (&pthread_queue_idle->mutex);      
                            &pthread_queue_idle->mutex);      
      
        /*if this is the last idle thread ,modiry the head and rear pointor */ 
    if (pthread_queue_idle->head == pthread_queue_idle->rear)
    {
      pthread_queue_idle->head = NULL;
      pthread_queue_idle->rear = NULL;
    }      
        /*if idle thread number>2, get the first one,modify the head pointor  */ 
    else
    {
      pthread_queue_idle->head = pthread_queue_idle->head->next;
      pthread_queue_idle->head->prev = NULL;
    }
      
      
        /*modify the  task attribute. */ 
    pthread_mutex_lock (&temp_task->mutex);
      
    temp_task->next = NULL;
    temp_task->flag = 1;
      
        /*modify the idle thread attribute. */ 
    pthread_mutex_lock (&temp_thread->mutex);
      
    temp_thread->work = temp_task;
    temp_thread->next = NULL;
    temp_thread->prev = NULL;
      
        /*add the thread assinged task to the busy queue. */ 
    pthread_mutex_lock (&pthread_queue_busy->mutex);      
        /*if this is the first one in busy queue */ 
    if (pthread_queue_busy->head == NULL)        
    {
       pthread_queue_busy->head = temp_thread;          
    else        
    {          
            /*insert in thre front of the queue */ 
      pthread_queue_busy->head->prev = temp_thread;          
    pthread_mutex_unlock (&pthread_queue_busy->mutex);      
        /*signal the child thread to exec the work */ 
    pthread_cond_signal (&temp_thread->cond);    

/*
*code to process the new client in every chilld pthead.
*ptr: the fd come from listen thread that can communicate to the client.
*return:nothing. void * only used to avoid waring.
*/
prcoess_client (void *ptr) 
{  

  

    /*get the command mesg from client */ 
  if (-1 == recv (net_fd, &client_info, sizeof (client_info), 0))    
  {      
    goto clean;    
  /* if the client requre the attribute of one file. */
  {      
    {          
       goto clean;       
      
      
        /*send info of the file */ 
    if (-1 == send (net_fd, msgbuf, strlen (msgbuf) + 1, 0))
    {
      printf ("send msg error\n");
      close (net_fd);
	  goto clean;
    }
	
    close (net_fd);      
  
  else    
  {
    int local_begin = ntohl (client_info.local_begin);  /* the content begining location. */    
     /* open the src file and get the real content. */ 
    {          
      goto clean;	  
	/*seek the read local to the real location. */
      
    do        
    {          
      
	  /*read 1024bytes from file everytome, if the last one,read the real length. */
      else            
      {              
      
      /*send the data to client. */	  
      {              
	  
  return ;
  
clean:
  sys_clean();

/*
*task_manager: get new task and add to the tail of the task_link.
*ptr: no used. just avoid warning.
*return:nothing.
*/ 

task_manager (void *ptr) 
{
  {      

  struct ifreq ifr;
  
  
  {      
  
  
  myaddr.sin_addr.s_addr =
      ((struct sockaddr_in *) &(ifr.ifr_addr))->sin_addr.s_addr;

  {      
    goto clean;   
  {      
    goto clean;   
 
    /*i is the id of the task */ 
  int i;  
  {      
        (newfd = accept (listen_fd, (struct sockaddr *) &client, &len)))        
    {          
      goto clean;        
    {          
        /*
         *initial the attribute of the task.
         *because this task havn't add to system,so,no need lock the mutex.
         */ 
        
      
        /*add new task to task_link */ 
    pthread_mutex_lock (&task_queue_head->mutex);      
        /*find the tail of the task link and add the new one to tail */ 
    temp = task_queue_head->head;
      
    {          
    else        
    {          
        
        /*signal the manager thread , no task coming */ 
    pthread_cond_signal (&task_queue_head->cond);    
  
  return ;
  
clean:  
  sys_clean();

/*
*monitor: get the system info 
*ptr: not used ,only to avoid warning for pthread_create
*return: nothing.
*/ 
void *
monitor (void *ptr) 
{  
    /*in order to prevent warning. */ 
  ptr = ptr;  
 
  {      
        /*output the busy thread works one by one */ 
    temp_thread = pthread_queue_busy->head;
		
    {          
  

/*
*sys_clean: clean the system . 
*this function code need to do to make it more stronger.
*/
sys_clean (void) 
{
  printf("the system exit abnormally\n");  