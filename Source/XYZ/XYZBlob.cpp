#include "XYZBlob.h"
#include "XYZAction.h"

void UXYZBlob::InitializeBlob() {
    Head = MakeShared<FActionList>();
    Tail = MakeShared<FActionList>();

    Head->Next = Tail;
    Tail->Previous = Head;
    Head->Action = nullptr;
    Tail->Action = nullptr;

    Head->CompletedAgents = AgentsInBlob;

    AgentToNodeCache.Empty();
    ActionListSize = 0;
    for (AXYZActor* Agent : AgentsInBlob) {
        if (Agent) {
            AgentToNodeCache.Add(Agent, Head);
        }
    }
}
void UXYZBlob::ProcessBlob()
{
    if (!IsBlobProcessable()) {
        return;
    }

    TSharedPtr<FActionList> CurrentNodePtr = Head->Next;
    if (!Head.Get()->CompletedAgents.IsEmpty()) {
        if (Head->Next) {
            for (AXYZActor* Agent : Head->CompletedAgents) {
                if (Agent) {
                    Head->Next.Get()->QueuedAgents.Add(Agent);
                    AgentToNodeCache.Add(Agent, Head->Next);
                }
            }
            Head->CompletedAgents.Empty();
        }
    }
    while (CurrentNodePtr != nullptr) {
        FActionList* CurrentNode = CurrentNodePtr.Get();
        UXYZAction* CurrentAction = CurrentNode->Action;
        if (CurrentNodePtr == Tail || !CurrentAction) {
            break;
        }
        // Process all queued Agents
        // Add queued agents to processing set
        // clear queued agent set
        if (!CurrentNode->QueuedAgents.IsEmpty()) {
            CurrentAction->ProcessAction(CurrentNode->QueuedAgents);
            for (AXYZActor* Agent : CurrentNode->QueuedAgents) {
                if (Agent) {
                    CurrentNode->ProcessingAgents.Add(Agent);
                }
            }
            CurrentNode->QueuedAgents.Empty();
        }

        // Check agents is they are complete
        // send them to copmpleted set if so
        if (!CurrentNode->ProcessingAgents.IsEmpty()) {
            TSet<AXYZActor*> AgentsToBeCompleted;
            for (AXYZActor* Agent : CurrentNode->ProcessingAgents) {
                if (Agent) {
                    if (CurrentAction) {
                        if (CurrentAction->HasAgentComplete(Agent)) {
                            AgentsToBeCompleted.Add(Agent);
                        }
                    }
                }
                //if (Agent && CurrentAction && CurrentAction->HasAgentComplete(Agent)) {
                //    AgentsToBeCompleted.Add(Agent);
                //}
            }
            for (AXYZActor* Agent : AgentsToBeCompleted) {
                CurrentNode->ProcessingAgents.Remove(Agent);
                CurrentNode->CompletedAgents.Add(Agent);
            }
        }

        // Move copleted agents to the next node
        // Update agent-node cache
        if (!CurrentNode->CompletedAgents.IsEmpty()) {
            if (CurrentNode->Next) {
                for (AXYZActor* Agent : CurrentNode->CompletedAgents) {
                    if (Agent) {
                        CurrentNode->Next.Get()->QueuedAgents.Add(Agent);
                        AgentToNodeCache.Add(Agent, CurrentNode->Next);
                    }
                }
                CurrentNode->CompletedAgents.Empty();
            }
        }
        CurrentNodePtr = CurrentNodePtr.Get()->Next;
    }
    CurrentNodePtr = Head->Next;
    while (CurrentNodePtr != Tail) {
        if (CurrentNodePtr->QueuedAgents.IsEmpty() &&
            CurrentNodePtr->ProcessingAgents.IsEmpty() &&
            CurrentNodePtr->CompletedAgents.IsEmpty()) {
            CurrentNodePtr->Previous->Next = CurrentNodePtr->Next;
            CurrentNodePtr->Next->Previous = CurrentNodePtr->Previous;
            CurrentNodePtr->Action = nullptr;
            ActionListSize--;
        }
        else {
            break;
        }
        CurrentNodePtr = CurrentNodePtr.Get()->Next;
    }

}

void UXYZBlob::AddAction(UXYZAction* Action) {
    if (Head && Tail) {
        TSharedPtr<FActionList> NewNode = MakeShared<FActionList>();
        NewNode.Get()->Next = Tail;
        NewNode.Get()->Previous = Tail.Get()->Previous;
        NewNode.Get()->Action = Action;
        Tail.Get()->Previous->Next = NewNode;
        Tail.Get()->Previous = NewNode;
        ActionListSize++;
    }
}

void UXYZBlob::RemoveAgent(AXYZActor* Agent) {
    if (Agent) {
        AgentsInBlob.Remove(Agent);
        if (AgentToNodeCache.Contains(Agent)) {
            AgentToNodeCache[Agent].Get()->RemoveAgent(Agent);
            AgentToNodeCache.Remove(Agent);
        }
    }
}

bool UXYZBlob::IsBlobProcessable() {
    return !AgentsInBlob.IsEmpty()
        && ActionListSize > 0
        && Head.Get()->Next != Tail
        && ActionListSize;
}
