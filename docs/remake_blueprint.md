# PigKiller Remake Blueprint

## Remake Goals

1. Make character and balance configs flexible/readable: **character names in config instead of class names**.
2. Expand weapon progression (levels, modifiers, costs, character/class requirements).
3. Add a dedicated armor system: **equipment + armor market**.
4. Add an ASCII renderer over the current UI so the player can see world state (base, travel, upgrades, battle).

---

## 1) New Configuration Model

### Current Problem
- Logic and data are mixed in code.
- Adding new characters/items does not scale well.

### Proposed Structure
Create a `GameData` layer loaded from JSON, for example:

- `data/characters.json` - characters (id, displayName, base stats, starting weapon, starting armor).
- `data/weapons.json` - weapons + upgrade tree.
- `data/armor.json` - armor + upgrades.
- `data/locations.json` - travel map + locks.
- `data/ascii_scenes.json` - ASCII scenes by key.

### Identity Rule
- Always use a **stable id** (`"pig_leader"`),
- show `displayName` to the player (`"Chief Pig"`).

This makes localization/name changes safe without breaking logic.

---

## 2) Weapon Upgrades: Practical Model

### Recommended Compromise
Keep implementation lightweight with 2 layers:

1. **Global template level**
   - Upgrade weapon templates in forge/workshop.
2. **Per-instance weapon modification**
   - +damage / +crit / +accuracy (limited slots).

### Why this works
- Adds depth.
- Avoids a heavy full-RPG inventory model.
- Compatible with current weapon-swap flow.

### Balance
- Every upgrade has a cost, required character level, and tier cap.
- Persistence: each weapon has `instanceId` and active modifiers.

---

## 3) Armor and a Second Market

### Additions
- Armor slot per fighter (`armorId`).
- Incoming damage formula:
  - `finalDamage = max(1, rawDamage - armorFlatReduction)`
  - then `% reduction` (if present).

### Economy
- Keep current weapon market.
- Add armor market as a separate section:
  - `1. Weapons`
  - `2. Armor`
- Armor may include durability (optional), tier, and passive bonus.

---

## 4) ASCII Renderer (Main Point)

### Concept
Render an ASCII scene before each menu for the current screen.

```text
+----------------------------------+
| [ASCII scene]                    |
|                                  |
+----------------------------------+
| 1) ...                           |
| 2) ...                           |
| > Input                          |
+----------------------------------+
```

### Scene Keys
- `base_tavern_interior`
- `travel_map`
- `upgrade_party_overview`
- `battle_left_right`

### Render Variants
1. **Static**: print predefined scenes.
2. **Parameterized**: replace placeholders (`{{playerName}}`, `{{enemyName}}`, hp bars).

Start with static scenes + 2-3 placeholders.

---

## Suggested Delivery Sequence

### Sprint 1: Data & Loading Layer
- Add JSON files + key validation.
- Move magic values from code to config.

### Sprint 2: Armor + Armor Market
- Add armor to character model.
- Add buy/equip menu flow.

### Sprint 3: Weapon Upgrades
- Implement tiers + modifiers.
- Add upgrade UI.

### Sprint 4: ASCII Renderer
- Render scenes for base/travel/upgrade/battle.
- Add key + parameter support.

### Sprint 5: Polish
- Economy balance pass.
- UI quality improvements.
- Regression scenarios.

---

## Minimum Technical Requirements to Start

1. Add a JSON library (`nlohmann/json`) or equivalent.
2. Create a single `GameContext` with:
   - current screen,
   - player state,
   - loaded data references.
3. Add renderer API:
   - `RenderScene(sceneKey, context)`

---

## Risks and Mitigations

- **Risk:** too many features at once.
  - **Mitigation:** ship via feature flags/sprints.
- **Risk:** broken configs break the game.
  - **Mitigation:** schema validation + default fallback configs.
- **Risk:** ASCII renderer hurts UX.
  - **Mitigation:** strict frame, limited scene height, fixed width/font.
