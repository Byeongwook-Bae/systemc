/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2011 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  sc_method_process.h -- Method process declarations

  Original Author: Andy Goodrich, Forte Design Systems, 4 August 2005
               

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

// $Log: sc_method_process.h,v $
// Revision 1.11  2011/02/19 08:30:53  acg
//  Andy Goodrich: Moved process queueing into trigger_static from
//  sc_event::notify.
//
// Revision 1.10  2011/02/18 20:27:14  acg
//  Andy Goodrich: Updated Copyrights.
//
// Revision 1.9  2011/02/17 19:51:34  acg
//  Andy Goodrich:
//    (1) Changed the signature of trigger_dynamic back to a bool.
//    (2) Removed ready_to_run().
//    (3) Simplified process control usage.
//
// Revision 1.8  2011/02/16 22:37:30  acg
//  Andy Goodrich: clean up to remove need for ps_disable_pending.
//
// Revision 1.7  2011/02/13 21:47:37  acg
//  Andy Goodrich: update copyright notice.
//
// Revision 1.6  2011/02/01 21:05:05  acg
//  Andy Goodrich: Changes in trigger_dynamic methods to handle new
//  process control rules about event sensitivity.
//
// Revision 1.5  2011/01/18 20:10:44  acg
//  Andy Goodrich: changes for IEEE1666_2011 semantics.
//
// Revision 1.4  2009/07/28 01:10:53  acg
//  Andy Goodrich: updates for 2.3 release candidate.
//
// Revision 1.3  2009/05/22 16:06:29  acg
//  Andy Goodrich: process control updates.
//
// Revision 1.2  2008/05/22 17:06:25  acg
//  Andy Goodrich: updated copyright notice to include 2008.
//
// Revision 1.1.1.1  2006/12/15 20:20:05  acg
// SystemC 2.3
//
// Revision 1.7  2006/05/08 17:57:13  acg
//  Andy Goodrich: Added David Long's forward declarations for friend functions
//  to keep the Microsoft C++ compiler happy.
//
// Revision 1.6  2006/04/20 17:08:17  acg
//  Andy Goodrich: 3.0 style process changes.
//
// Revision 1.5  2006/04/11 23:13:21  acg
//   Andy Goodrich: Changes for reduced reset support that only includes
//   sc_cthread, but has preliminary hooks for expanding to method and thread
//   processes also.
//
// Revision 1.4  2006/01/24 20:49:05  acg
// Andy Goodrich: changes to remove the use of deprecated features within the
// simulator, and to issue warning messages when deprecated features are used.
//
// Revision 1.3  2006/01/13 18:44:29  acg
// Added $Log to record CVS changes into the source.
//

#if !defined(sc_method_process_h_INCLUDED)
#define sc_method_process_h_INCLUDED

#include "sysc/kernel/sc_process.h"
#include "sysc/kernel/sc_spawn_options.h"
#include "sysc/kernel/sc_cor.h"
#include "sysc/kernel/sc_event.h"

namespace sc_core {

// forward function and class declarations:

void sc_method_cor_fn( void* );
void sc_cmethod_cor_fn( void* );
void sc_set_stack_size( sc_method_handle, std::size_t );
class sc_event;
class sc_module;
class sc_process_table;
class sc_process_handle;
class sc_simcontext;
class sc_runnable;

void next_trigger( sc_simcontext* );
void next_trigger( const sc_event&, sc_simcontext* );
void next_trigger( const sc_event_or_list&, sc_simcontext* );
void next_trigger( const sc_event_and_list&, sc_simcontext* );
void next_trigger( const sc_time&, sc_simcontext* );
void next_trigger( const sc_time&, const sc_event&, sc_simcontext* );
void next_trigger( const sc_time&, const sc_event_or_list&, sc_simcontext* );
void next_trigger( const sc_time&, const sc_event_and_list&, sc_simcontext* );

//==============================================================================
// sc_method_process -
//
//==============================================================================
class sc_method_process : public sc_process_b {
    friend void sc_method_cor_fn( void* );
    friend void sc_cmethod_cor_fn( void* );
    friend void sc_set_stack_size( sc_method_handle, std::size_t );
    friend class sc_event;
    friend class sc_module;
    friend class sc_process_table;
    friend class sc_process_handle;
    friend class sc_simcontext;
    friend class sc_runnable;

    friend void next_trigger( sc_simcontext* );
    friend void next_trigger( const sc_event&,
                  sc_simcontext* );
    friend void next_trigger( const sc_event_or_list&,
                  sc_simcontext* );
    friend void next_trigger( const sc_event_and_list&,
                  sc_simcontext* );
    friend void next_trigger( const sc_time&,
                  sc_simcontext* );
    friend void next_trigger( const sc_time&, const sc_event&,
                  sc_simcontext* );
    friend void next_trigger( const sc_time&, const sc_event_or_list&,
                  sc_simcontext* );
    friend void next_trigger( const sc_time&, const sc_event_and_list&,
                  sc_simcontext* );

  public:
    sc_method_process( const char* name_p, bool free_host,
        SC_ENTRY_FUNC method_p, sc_process_host* host_p, 
        const sc_spawn_options* opt_p );

    virtual ~sc_method_process();

    virtual const char* kind() const
        { return "sc_method_process"; }

  protected:
    virtual void disable_process(
        sc_descendant_inclusion_info descendants = SC_NO_DESCENDANTS );
    virtual void enable_process(
        sc_descendant_inclusion_info descendants = SC_NO_DESCENDANTS );
    virtual void kill_process(
        sc_descendant_inclusion_info descendants = SC_NO_DESCENDANTS );
    sc_method_handle next_exist();
    sc_method_handle next_runnable();
    void clear_trigger();
    void next_trigger( const sc_event& );
    void next_trigger( const sc_event_or_list& );
    void next_trigger( const sc_event_and_list& );
    void next_trigger( const sc_time& );
    void next_trigger( const sc_time&, const sc_event& );
    void next_trigger( const sc_time&, const sc_event_or_list& );
    void next_trigger( const sc_time&, const sc_event_and_list& );
    virtual void queue_for_execution();
    virtual void resume_process(
        sc_descendant_inclusion_info descendants = SC_NO_DESCENDANTS );
    void set_next_exist( sc_method_handle next_p );
    void set_next_runnable( sc_method_handle next_p );
    void set_stack_size( std::size_t size );
    virtual void suspend_process( 
        sc_descendant_inclusion_info descendants = SC_NO_DESCENDANTS );
    virtual void throw_reset( bool async );
    virtual void throw_user( const sc_throw_it_helper& helper,
        sc_descendant_inclusion_info descendants = SC_NO_DESCENDANTS );
    bool trigger_dynamic( sc_event* );
    inline void trigger_static();

  protected:
    sc_cor*                          m_cor;        // Thread's coroutine.
    std::size_t                      m_stack_size; // Thread stack size.
    std::vector<sc_process_monitor*> m_monitor_q;  // Thread monitors.

  private: // disabled
    sc_method_process( const sc_method_process& );
    const sc_method_process& operator = ( const sc_method_process& );

};


inline
void
sc_method_process::next_trigger( const sc_event& e )
{
    clear_trigger();
    e.add_dynamic( this );
    m_event_p = &e;
    m_trigger_type = EVENT;
}

inline
void
sc_method_process::next_trigger( const sc_event_or_list& el )
{
    clear_trigger();
    el.add_dynamic( this );
    m_event_list_p = &el;
    m_trigger_type = OR_LIST;
}

inline
void
sc_method_process::next_trigger( const sc_event_and_list& el )
{
    clear_trigger();
    el.add_dynamic( this );
    m_event_list_p = &el;
    m_event_count = el.size();
    m_trigger_type = AND_LIST;
}

inline
void
sc_method_process::next_trigger( const sc_time& t )
{
    clear_trigger();
    m_timeout_event_p->notify_internal( t );
    m_timeout_event_p->add_dynamic( this );
    m_trigger_type = TIMEOUT;
}

inline
void
sc_method_process::next_trigger( const sc_time& t, const sc_event& e )
{
    clear_trigger();
    m_timeout_event_p->notify_internal( t );
    m_timeout_event_p->add_dynamic( this );
    e.add_dynamic( this );
    m_event_p = &e;
    m_trigger_type = EVENT_TIMEOUT;
}

inline
void
sc_method_process::next_trigger( const sc_time& t, const sc_event_or_list& el )
{
    clear_trigger();
    m_timeout_event_p->notify_internal( t );
    m_timeout_event_p->add_dynamic( this );
    el.add_dynamic( this );
    m_event_list_p = &el;
    m_trigger_type = OR_LIST_TIMEOUT;
}

inline
void
sc_method_process::next_trigger( const sc_time& t, const sc_event_and_list& el )
{
    clear_trigger();
    m_timeout_event_p->notify_internal( t );
    m_timeout_event_p->add_dynamic( this );
    el.add_dynamic( this );
    m_event_list_p = &el;
    m_event_count = el.size();
    m_trigger_type = AND_LIST_TIMEOUT;
}

//------------------------------------------------------------------------------
//"sc_method_process::queue_for_execution"
//
//------------------------------------------------------------------------------
inline
void sc_method_process::queue_for_execution()
{
    if ( !is_runnable() )
	simcontext()->push_runnable_method(this);
}

inline
void sc_method_process::set_next_exist(sc_method_handle next_p)
{
    m_exist_p = next_p;
}

inline
sc_method_handle sc_method_process::next_exist()
{
    return (sc_method_handle)m_exist_p;
}


inline
void sc_method_process::set_next_runnable(sc_method_handle next_p)
{
    m_runnable_p = next_p;
}

inline
sc_method_handle sc_method_process::next_runnable()
{
    return (sc_method_handle)m_runnable_p;
}

//------------------------------------------------------------------------------
//"sc_method_process::trigger_static"
//
// This inline method returns true if this object instance should be placed on 
// the queue of runnable processes. This is the case if the following criteria
// are met:
//   (1) The process is in a runnable state.
//   (2) The process is not already on the run queue.
//   (3) The process is expecting a static trigger, dynamic event waits take
//       priority.
//------------------------------------------------------------------------------
inline
void
sc_method_process::trigger_static()
{
    if ( (m_state & ps_bit_disabled) || is_runnable() || 
          m_trigger_type != STATIC )
        return;
    if ( m_state & ps_bit_disabled ) return;

    // If we get here then the method is has satisfied its wait, if its 
    // suspended mark its state as ready to run. If its not suspended then 
    // push it onto the runnable queue.

    if ( m_state & ps_bit_suspended )
    {
        m_state = m_state | ps_bit_ready_to_run;
    }
    else
    {
        simcontext()->push_runnable_method(this);
    }
}

} // namespace sc_core 

#endif // !defined(sc_method_process_h_INCLUDED)