#include "IFX_Framework.h"
#include "IFX_DbC.h"
#include "IFX_Event_Manager.h"

#include "../IFX_Ioctl/IFX_Ioctl_Interface.h"
#include "../IFX_Io_Manager/IFX_Io_Manager.h"
#include "../IFX_Memory/IFX_Memory.h"
#include "../IFX_Tasks/IFX_Tasks.h"

#if (IFX_CFG_MULTI_IO == 1)
    #include "../IFX_TaskMan/IFX_AppNoteTaskMan.h"
#endif

#include "../IFX_Clk_Pwr/IFX_Clk_Pwr.h"

/* private  typedefs
****************************************************************/
/** Working modes of Event System */
typedef enum IFX_EVM_OP_MODE
{
    eIFX_EVM_STARTUP_PHASE = 0,
    eIFX_EVM_MULTIO_MODE = 0xAF
} IFX_EVM_OP_MODE;

/** Structure with pending events and tasks waiting for event group */
typedef struct EVENT_GROUP_td
{
#if (IFX_CFG_MULTI_IO == 1)
    IFX_APPNOTE_TCB *Next;            /*!< Pointer to the next task listening to events in group*/
#endif
    IFX_EVENT_MASK  PendingMask;        /*!< Events that are currently pending */
} EVENT_GROUP;

/** Structure holding details about pending events and waiting tasks */
typedef struct EVENT_SYSTEM
{
    EVENT_GROUP Groups[EVENT_GROUP_COUNT];  /*!< Array of available event groups */
    IFX_EVM_OP_MODE OperationMode;          /*!< Initialization stage of Event System  */
} EVENT_SYSTEM;
