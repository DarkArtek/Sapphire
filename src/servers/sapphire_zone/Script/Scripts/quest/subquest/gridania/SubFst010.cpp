#include "../../../ScriptObject.h"

// Quest Script: SubFst010_00001
// Quest Name: A Good Adventurer Is Hard to Find
// Quest ID: 65537
// Start NPC: 1000146
// End NPC: 1000195

class SubFst010 : public EventScript
{
private:
   static constexpr auto SEQ_0 = 0;
   static constexpr auto SEQ_FINISH = 255;
   static constexpr auto ACTOR0 = 1000146;
   static constexpr auto ACTOR1 = 1000195;
   static constexpr auto SEQ_0_ACTOR0 = 0;
   static constexpr auto SEQ_1_ACTOR1 = 1;

   void Scene00000( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         if( param2 == 1 ) // accept quest
            player.updateQuest( getId(), SEQ_FINISH );
      };

      player.eventPlay( getId(), 0, NONE, callback );
   }

   void Scene00001( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         if( param2 == 1 ) // finish quest
         {
            if( player.giveQuestRewards( getId(), 0 ) )
               player.finishQuest( getId() );
         }
      };

      player.eventPlay( getId(), 1, NONE, callback );
   }

public:
   SubFst010() : EventScript( 65537 ) {}

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

      if( actor == ACTOR0 )
         Scene00000( player );
      else if( actor == ACTOR1 )
         Scene00001( player );
   }
};