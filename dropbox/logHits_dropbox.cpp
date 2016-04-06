#include <iostream>
#include <queue>
using namespace std;


/**
  Question: Implmement a hit counts system in a server, hits live locally (cannot just query a database).
            We don't care about any data other than the # of hits in the last 5 minutes.
            System is not multithreaded, no need to use atomical operations.

            -> log_hit() -> server call this whenever someone visits

            -> get_hits_last_5_min() -> dashboard calls this to show # hits from last 5 minutes

   CodePad: https://coderpad.io/AQHY9P64
*/

const time_t SECS_IN_5_MINS = 5*60; // 5 mins

time_t m_timeOffset = 0;
queue<time_t> m_hitsQueue;

time_t getCurrentTime(bool withOffset = true){
  time_t now;
  time(&now);
  if (withOffset)
    now += m_timeOffset;
  return now;
}

void delete_hits_over_5_mins_old(){
    time_t now = getCurrentTime( );
    while (m_hitsQueue.size()){
      time_t hit = m_hitsQueue.front();
      if (now - hit >= SECS_IN_5_MINS )
        // hit is older than 5 minutes, delete it form the queue.
        m_hitsQueue.pop();
      else
        // next hits are "younger", so break here.
        break;
    }
}

void log_hits(){
    time_t now = getCurrentTime();
    // clear hits over 5 mins every time we log a hit so we don't overflow.
    delete_hits_over_5_mins_old();
    m_hitsQueue.push(now);
}

size_t get_hits_last_5_min(){
    delete_hits_over_5_mins_old();
    // for (time_t &time : m_hitsQueue){
    //     cout << "hits in last 5 min: " << time << endl;
    // }
    size_t hits = m_hitsQueue.size();
    return hits;
}

int main(){
  // log 3 hits
  log_hits();
  log_hits();
  log_hits();
  
  //simulate that 5 minutes have passed...
  m_timeOffset = SECS_IN_5_MINS + 10;

  // log 2 hits
  log_hits();
  log_hits();
  
  size_t hits = get_hits_last_5_min();
  cout << "hits in las 5 mins: " << hits << endl; 
}
