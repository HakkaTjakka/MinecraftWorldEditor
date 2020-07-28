return
{
	cEntity =
	{
		Functions =
		{
			AddPosX =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_AddPosX",
						},
					},
					Returns =
					{
					},
				},
			},
			AddPosY =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_AddPosY",
						},
					},
					Returns =
					{
					},
				},
			},
			AddPosZ =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_AddPosZ",
						},
					},
					Returns =
					{
					},
				},
			},
			AddPosition =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_AddPosX",
						},
						{
							Type = "double",
							Name = "a_AddPosY",
						},
						{
							Type = "double",
							Name = "a_AddPosZ",
						},
					},
					Returns =
					{
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_AddPos",
						},
					},
					Returns =
					{
					},
				},
			},
			AddSpeed =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_AddSpeedX",
						},
						{
							Type = "double",
							Name = "a_AddSpeedY",
						},
						{
							Type = "double",
							Name = "a_AddSpeedZ",
						},
					},
					Returns =
					{
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_AddSpeed",
						},
					},
					Returns =
					{
					},
				},
			},
			AddSpeedX =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_AddSpeedX",
						},
					},
					Returns =
					{
					},
				},
			},
			AddSpeedY =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_AddSpeedY",
						},
					},
					Returns =
					{
					},
				},
			},
			AddSpeedZ =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_AddSpeedZ",
						},
					},
					Returns =
					{
					},
				},
			},
			ApplyArmorDamage =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "DamageBlocked",
						},
					},
					Returns =
					{
					},
					Desc = "Applies damage to the armor after the armor blocked the given amount",
				},
			},
			ArmorCoversAgainst =
			{
				{
					Params =
					{
						{
							Type = "eDamageType",
							Name = "a_DamageType",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns whether armor will protect against the specified damage type",
				},
			},
			Destroy =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_ShouldBroadcast",
						},
					},
					Returns =
					{
					},
					Desc = "Destroys the entity and schedules it for memory freeing; if a_ShouldBroadcast is set to true, broadcasts the DestroyEntity packet",
				},
			},
			DoesPreventBlockPlacement =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns whether blocks can be placed intersecting this entities' hitbox",
				},
			},
			GetAirDrag =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "float",
						},
					},
				},
			},
			GetAirLevel =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Gets remaining air of a monster",
				},
			},
			GetArmorCoverAgainst =
			{
				{
					Params =
					{
						{
							Type = "cEntity",
							Name = "a_Attacker",
						},
						{
							Type = "eDamageType",
							Name = "a_DamageType",
						},
						{
							Type = "int",
							Name = "a_RawDamage",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns the hitpoints out of a_RawDamage that the currently equipped armor would cover",
				},
			},
			GetChunkX =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
			},
			GetChunkZ =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
			},
			GetClass =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const char*",
						},
					},
					Desc = "Returns the topmost class name for the object",
				},
			},
			GetClassStatic =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const char*",
						},
					},
					IsStatic = true,
					Desc = "Returns the class name of this class",
				},
			},
			GetEnchantmentBlastKnockbackReduction =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "float",
						},
					},
					Desc = "Returns explosion knock back reduction percent from blast protection level\
	@return knock back reduce percent",
				},
			},
			GetEnchantmentCoverAgainst =
			{
				{
					Params =
					{
						{
							Type = "cEntity",
							Name = "a_Attacker",
						},
						{
							Type = "eDamageType",
							Name = "a_DamageType",
						},
						{
							Type = "int",
							Name = "a_Damage",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns the hitpoints that the currently equipped armor's enchantments would cover",
				},
			},
			GetEntityType =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cEntity::eEntityType",
						},
					},
					Desc = "Spawns the entity in the world; returns true if spawned, false if not (plugin disallowed).\
	Adds the entity to the world.",
				},
			},
			GetEquippedBoots =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Returns the currently equipped boots; empty item if none",
				},
			},
			GetEquippedChestplate =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Returns the currently equipped chestplate; empty item if none",
				},
			},
			GetEquippedHelmet =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Returns the currently equipped helmet; empty item if none",
				},
			},
			GetEquippedLeggings =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Returns the currently equipped leggings; empty item if none",
				},
			},
			GetEquippedWeapon =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Returns the curently equipped weapon; empty item if none",
				},
			},
			GetGravity =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "float",
						},
					},
				},
			},
			GetHeadYaw =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetHealth =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "float",
						},
					},
					Desc = "Returns the health of this entity",
				},
			},
			GetHeight =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetInvulnerableTicks =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Gets the invulnerable ticks from the entity",
				},
			},
			GetKnockbackAmountAgainst =
			{
				{
					Params =
					{
						{
							Type = "cEntity",
							Name = "a_Receiver",
						},
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
					Desc = "Returns the knockback amount that the currently equipped items would cause to a_Receiver on a hit",
				},
			},
			GetLookVector =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
			},
			GetMass =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetMaxHealth =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "float",
						},
					},
				},
			},
			GetOffHandEquipedItem =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Returns the currently offhand equipped item; empty item if none",
				},
			},
			GetParentClass =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const char*",
						},
					},
					Desc = "Returns the topmost class's parent class name for the object. cEntity returns an empty string (no parent).",
				},
			},
			GetPitch =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetPosX =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetPosY =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetPosZ =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetRawDamageAgainst =
			{
				{
					Params =
					{
						{
							Type = "cEntity",
							Name = "a_Receiver",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns the hitpoints that this pawn can deal to a_Receiver using its equipped items",
				},
			},
			GetRoll =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetSpeedX =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetSpeedY =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetSpeedZ =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetTicksAlive =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Gets number of ticks this entity has existed for",
				},
			},
			GetUniqueID =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
			},
			GetWidth =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetWorld =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cWorld",
						},
					},
				},
			},
			GetYaw =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			HandleSpeedFromAttachee =
			{
				{
					Params =
					{
						{
							Type = "float",
							Name = "a_Forward",
						},
						{
							Type = "float",
							Name = "a_Sideways",
						},
					},
					Returns =
					{
					},
				},
			},
			Heal =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_HitPoints",
						},
					},
					Returns =
					{
					},
					Desc = "Heals the specified amount of HPs",
				},
			},
			IsA =
			{
				{
					Params =
					{
						{
							Type = "char*",
							Name = "a_ClassName",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the entity is of the specified class or a subclass (cPawn's IsA(\"cEntity\") returns true)",
				},
			},
			IsBoat =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsCrouched =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsDestroyed =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Deprecated. Use IsTicking instead.",
				},
			},
			IsEnderCrystal =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsExpOrb =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsFallingBlock =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsFireproof =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsFloater =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsHeadInWater =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if any part of the entity is in a water block",
				},
			},
			IsInFire =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if any part of the entity is in a fire block",
				},
			},
			IsInLava =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if any part of the entity is in a lava block",
				},
			},
			IsInWater =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if any part of the entity is in a water block",
				},
			},
			IsInvisible =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsItemFrame =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsLeashKnot =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsMinecart =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsMob =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsOnFire =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Makes speed is not over 20. Max speed is 20 blocks / second",
				},
			},
			IsOnGround =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns whether the entity is on ground or not",
				},
			},
			IsPainting =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsPawn =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsPickup =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsPlayer =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsProjectile =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsRclking =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsRiding =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsSprinting =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsTNT =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsTicking =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the entity is valid and ticking. Returns false if the entity is not ticking and is about to leave\
	its current world either via teleportation or destruction.\
	If this returns false, you must stop using the cEntity pointer you have.",
				},
			},
			Killed =
			{
				{
					Params =
					{
						{
							Type = "cEntity",
							Name = "a_Victim",
						},
					},
					Returns =
					{
					},
					Desc = "Called when the entity kills another entity",
				},
			},
			MoveToWorld =
			{
				{
					Params =
					{
						{
							Type = "cWorld",
							Name = "a_World",
						},
						{
							Type = "bool",
							Name = "a_ShouldSendRespawn",
						},
						{
							Type = "Vector3<double>",
							Name = "a_NewPosition",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "cWorld",
							Name = "a_World",
						},
						{
							Type = "bool",
							Name = "a_ShouldSendRespawn",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Moves entity to specified world, taking a world pointer",
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_WorldName",
						},
						{
							Type = "bool",
							Name = "a_ShouldSendRespawn",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Moves entity to specified world, taking a world name",
				},
			},
			ScheduleMoveToWorld =
			{
				{
					Params =
					{
						{
							Type = "cWorld",
							Name = "a_World",
						},
						{
							Type = "Vector3<double>",
							Name = "a_NewPosition",
						},
						{
							Type = "bool",
							Name = "a_ShouldSetPortalCooldown",
						},
						{
							Type = "bool",
							Name = "a_ShouldSendRespawn",
						},
					},
					Returns =
					{
					},
					Desc = "Schedules a MoveToWorld call to occur on the next Tick of the entity",
				},
			},
			SetAirDrag =
			{
				{
					Params =
					{
						{
							Type = "float",
							Name = "a_AirDrag",
						},
					},
					Returns =
					{
					},
				},
			},
			SetGravity =
			{
				{
					Params =
					{
						{
							Type = "float",
							Name = "a_Gravity",
						},
					},
					Returns =
					{
					},
				},
			},
			SetHeadYaw =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_HeadYaw",
						},
					},
					Returns =
					{
					},
				},
			},
			SetHealth =
			{
				{
					Params =
					{
						{
							Type = "float",
							Name = "a_Health",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the health of this entity; doesn't broadcast any hurt animation",
				},
			},
			SetInvulnerableTicks =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_InvulnerableTicks",
						},
					},
					Returns =
					{
					},
					Desc = "Set the invulnerable ticks from the entity",
				},
			},
			SetIsFireproof =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_IsFireproof",
						},
					},
					Returns =
					{
					},
					Desc = "Sets whether the entity is fireproof",
				},
			},
			SetMass =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_Mass",
						},
					},
					Returns =
					{
					},
				},
			},
			SetMaxHealth =
			{
				{
					Params =
					{
						{
							Type = "float",
							Name = "a_MaxHealth",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the maximum value for the health",
				},
			},
			SetPitch =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_Pitch",
						},
					},
					Returns =
					{
					},
				},
			},
			SetPitchFromSpeed =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Sets the pitch to match the speed vector (entity gies \"face-forward\")",
				},
			},
			SetPosX =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_PosX",
						},
					},
					Returns =
					{
					},
				},
			},
			SetPosY =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_PosY",
						},
					},
					Returns =
					{
					},
				},
			},
			SetPosZ =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_PosZ",
						},
					},
					Returns =
					{
					},
				},
			},
			SetPosition =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_PosX",
						},
						{
							Type = "double",
							Name = "a_PosY",
						},
						{
							Type = "double",
							Name = "a_PosZ",
						},
					},
					Returns =
					{
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Position",
						},
					},
					Returns =
					{
					},
				},
			},
			SetRoll =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_Roll",
						},
					},
					Returns =
					{
					},
				},
			},
			SetSpeed =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_SpeedX",
						},
						{
							Type = "double",
							Name = "a_SpeedY",
						},
						{
							Type = "double",
							Name = "a_SpeedZ",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the speed of the entity, measured in m / sec",
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Speed",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the speed of the entity, measured in m / sec",
				},
			},
			SetSpeedX =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_SpeedX",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the speed in the X axis, leaving the other speed components intact. Measured in m / sec.",
				},
			},
			SetSpeedY =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_SpeedY",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the speed in the Y axis, leaving the other speed components intact. Measured in m / sec.",
				},
			},
			SetSpeedZ =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_SpeedZ",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the speed in the Z axis, leaving the other speed components intact. Measured in m / sec.",
				},
			},
			SetYaw =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_Yaw",
						},
					},
					Returns =
					{
					},
				},
			},
			SetYawFromSpeed =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Sets the rotation to match the speed vector (entity goes \"face-forward\")",
				},
			},
			StartBurning =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_TicksLeftBurning",
						},
					},
					Returns =
					{
					},
					Desc = "Puts the entity on fire for the specified amount of ticks",
				},
			},
			SteerVehicle =
			{
				{
					Params =
					{
						{
							Type = "float",
							Name = "a_Forward",
						},
						{
							Type = "float",
							Name = "a_Sideways",
						},
					},
					Returns =
					{
					},
				},
			},
			StopBurning =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Stops the entity from burning, resets all burning timers",
				},
			},
			TakeDamage =
			{
				{
					Params =
					{
						{
							Type = "cEntity",
							Name = "a_Attacker",
						},
					},
					Returns =
					{
					},
					Desc = "Makes this pawn take damage from an attack by a_Attacker. Damage values are calculated automatically and DoTakeDamage() called",
				},
				{
					Params =
					{
						{
							Type = "eDamageType",
							Name = "a_DamageType",
						},
						{
							Type = "cEntity",
							Name = "a_Attacker",
						},
						{
							Type = "int",
							Name = "a_RawDamage",
						},
						{
							Type = "double",
							Name = "a_KnockbackAmount",
						},
					},
					Returns =
					{
					},
					Desc = "Makes this entity take the specified damage. The final damage is calculated using current armor, then DoTakeDamage() called",
				},
				{
					Params =
					{
						{
							Type = "eDamageType",
							Name = "a_DamageType",
						},
						{
							Type = "int",
							Name = "a_Attacker",
						},
						{
							Type = "int",
							Name = "a_RawDamage",
						},
						{
							Type = "double",
							Name = "a_KnockbackAmount",
						},
					},
					Returns =
					{
					},
					Desc = "Makes this entity take the specified damage. The final damage is calculated using current armor, then DoTakeDamage() called",
				},
				{
					Params =
					{
						{
							Type = "eDamageType",
							Name = "a_DamageType",
						},
						{
							Type = "cEntity",
							Name = "a_Attacker",
						},
						{
							Type = "int",
							Name = "a_RawDamage",
						},
						{
							Type = "float",
							Name = "a_FinalDamage",
						},
						{
							Type = "double",
							Name = "a_KnockbackAmount",
						},
					},
					Returns =
					{
					},
					Desc = "Makes this entity take the specified damage. The values are packed into a TDI, knockback calculated, then sent through DoTakeDamage()",
				},
			},
			TeleportToCoords =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_PosX",
						},
						{
							Type = "double",
							Name = "a_PosY",
						},
						{
							Type = "double",
							Name = "a_PosZ",
						},
					},
					Returns =
					{
					},
					Desc = "Teleports to the coordinates specified",
				},
			},
			TeleportToEntity =
			{
				{
					Params =
					{
						{
							Type = "cEntity",
							Name = "a_Entity",
						},
					},
					Returns =
					{
					},
					Desc = "Teleports to the entity specified",
				},
			},
		},
		Enums =
		{
			eEntityType =
			{
				{
					Name = "etBoat",
				},
				{
					Name = "etEnderCrystal",
				},
				{
					Name = "etEntity",
				},
				{
					Name = "etExpOrb",
				},
				{
					Name = "etFallingBlock",
				},
				{
					Name = "etFloater",
				},
				{
					Name = "etItemFrame",
				},
				{
					Name = "etLeashKnot",
				},
				{
					Name = "etMinecart",
				},
				{
					Name = "etMob",
				},
				{
					Name = "etMonster",
				},
				{
					Name = "etPainting",
				},
				{
					Name = "etPickup",
				},
				{
					Name = "etPlayer",
				},
				{
					Name = "etProjectile",
				},
				{
					Name = "etTNT",
				},
			},
		},
	},
}
