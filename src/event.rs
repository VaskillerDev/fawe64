use std::any::Any;
use std::collections::{HashMap, LinkedList};
use crate::node::NodeId;

#[derive(Debug, PartialEq, Copy, Clone, Hash, Eq)]
pub enum EventName {
    EUnknown = 0,

    EHpPointsChanged = 20,
    EHpPointsFilled = 21,
    EHpPointsOver = 22,
    EBoundingVolumeCollided = 23,

    EEnemyActionStateChanged = 30,
    EEnemyAttackBullet = 31,
    EEnemyHasGotBulletCollision = 32,

    ESwordAttackHit = 33,

    EPlayerAttackAnimationTimeout = 34,
    EPlayerHasGotBulletCollision = 35,
    EPlayerEnterDungeon = 36,
    EPlayerLeaveDungeon = 37,

    ELevelBorderContact = 38,
    ELevelChunkMoved = 39,

    ETimerExpired = 40
}

impl From<EventName> for u8 {
    fn from(value: EventName) -> Self {
        value as u8
    }
}

pub type FnHandler<T=Box<dyn Any>> = fn (args: T);

#[derive(Default)]
pub struct EventEmitter {
    map: HashMap<u8, LinkedList<FnHandler>>,
}

impl EventEmitter {

    /// register event and closure-handler
    pub fn on(&mut self, name : EventName, handler: FnHandler)   {
        let k: u8 = name.into();

        match self.map.get_mut(&k) {
            Some(ll) => {
                ll.push_back(handler);
            }
            None => {
                let mut ll = LinkedList::new();
                ll.push_back(handler);
                self.map.insert(k, ll);
            }
        }
    }

    /// emit event
    pub fn emit<T>(&mut self, name : EventName, args : Box<T> ) where T: Any + Clone {
        let vec = self.map.get_mut(&name.into()).unwrap();

        for handler in vec.iter() {
            handler(args.clone());
        }
    }
}



#[derive(Clone)]
pub struct PointsChangedEvent {
    pub node_id: NodeId,
    pub current_points: u16,
    //parent
}


#[derive(Clone)]
pub struct PointsOverEvent {
    node_id: NodeId,
    // parent
}


#[derive(Clone)]
pub struct PointsFilledEvent {
    node_id: NodeId
    // parent
}

#[derive(Clone)]
pub struct UnitActionStateChangedEvent {
    node_id: NodeId,
    // parent
}

