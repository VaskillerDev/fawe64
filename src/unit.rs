pub struct Unit {
    pub meta_data: UnitMetaData,

}

/// readonly in-game live instance
/// using for create Unit instance
pub struct UnitMetaData {
    // attack
    can_attack: bool,
    attack_type: UnitAttackType,

    // moving
    can_move: bool,
    move_speed: u8,
    move_type: UnitMoveType,

    // hitting
    can_get_hit: bool,
}

#[derive(Debug, PartialEq, Copy, Clone)]
pub enum UnitAttackType {
    UATMelee,
    UATRange,
}

#[derive(Debug, PartialEq, Copy, Clone)]
pub enum UnitMoveType {
    UMTGround,
    UMTFlying
}

