<h1>Cats</h1>
<ul>
<?php foreach ($categories as $cat): ?>
    <li><?php echo $cat->name; ?></li>
<?php endforeach; ?>
</ul>

<br />
<h1>Items</h1>
<?php foreach ($iron_folio_items as $item): ?>
    <li><?php echo $item->title; ?></li>
<?php endforeach; ?>

