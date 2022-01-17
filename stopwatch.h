/*
 * stopwatch.h
 *
 *  Created on: Jan 4, 2022
 *      Author: Matthew
 */

#ifndef SRC_STOPWATCH_H_
#define SRC_STOPWATCH_H_

uint32_t m_nStart;               //DEBUG Stopwatch start cycle counter value
uint32_t m_nStop;                //DEBUG Stopwatch stop cycle counter value

#define DEMCR_TRCENA    0x01000000

/* Core Debug registers */
#define DEMCR           (*((volatile uint32_t *)0xE000EDFC))
#define DWT_CTRL        (*(volatile uint32_t *)0xe0001000)
#define CYCCNTENA       (1<<0)
#define DWT_CYCCNT      ((volatile uint32_t *)0xE0001004)
#define CPU_CYCLES      *DWT_CYCCNT
#define CLK_SPEED         168000000 // EXAMPLE for CortexM4, EDIT as needed

#define STOPWATCH_START { m_nStart = *((volatile unsigned int *)0xE0001004);}
#define STOPWATCH_STOP  { m_nStop = *((volatile unsigned int *)0xE0001004);}
#define STOPWATCH_DUR   ( m_nStop - m_nStart)


static inline void stopwatch_reset(void)
{
    /* Enable DWT */
    DEMCR |= DEMCR_TRCENA;
    *DWT_CYCCNT = 0;
    /* Enable CPU cycle counter */
    DWT_CTRL |= CYCCNTENA;
}

static inline uint32_t stopwatch_getticks()
{
    return CPU_CYCLES;
}

static inline void stopwatch_delay(uint32_t ticks)
{
    uint32_t end_ticks = ticks + stopwatch_getticks();
    while(1)
    {
            if (stopwatch_getticks() >= end_ticks)
                    break;
    }
}

#endif /* SRC_STOPWATCH_H_ */
