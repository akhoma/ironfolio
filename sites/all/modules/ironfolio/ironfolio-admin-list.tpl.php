<?php
global $base_path, $language_url;
$current_url_path = $base_path;
$current_url_path .=  $language_url->prefix ?  $language_url->prefix . '/' : '';
?>
<div class="ironfolio-admin">
    <h1>language select</h1>
    <ul>
        <li><a href="<?php echo $base_path . 'en/' . "admin/ironfolio/" . $current_cat_id ?>">English</a></li>
        <li><a href="<?php echo $base_path . 'ru/' . "admin/ironfolio/" . $current_cat_id ?>">Русский</a></li>
    </ul>



    <h1>Cats</h1>
    <ul>
    <?php foreach ($categories as $cat): ?>
        <?php
            $cat_class = "";
               if ($current_cat_id == $cat->tid) {
                   $cat_class = 'active';
               }
        ?>
        <li class="<?php echo $cat_class; ?>">
            <a href="<?php echo $current_url_path . "admin/ironfolio/$cat->tid"; ?>"><?php echo $cat->name; ?></a>
        </li>
    <?php endforeach; ?>
    </ul>

    <br />
    <h1>Items</h1>
    <ul class="folioitems">
    <?php for($i = 0; $i < count($iron_folio_items); $i++): ?>
        <?php
            $item = $iron_folio_items[$i];
            $prev_item = isset($iron_folio_items[$i-1]) ? $iron_folio_items[$i-1] : false;
            $next_item = isset($iron_folio_items[$i+1]) ? $iron_folio_items[$i+1] : false;
        ?>
        <li>
            <?php echo $item->title; ?>
            <br />
            <?php echo $item->field_sort_order['und'][0]['value']; ?>
            <br />
            <?php if ($prev_item): ?>
                <a href="<?php echo $current_url_path . "admin/ironfolio/changesortorder/$item->nid/$prev_item->nid/"; ?>">Up</a>
            <?php endif ?>
            <br />
            <?php if ($next_item): ?>
                <a href="<?php echo $current_url_path . "admin/ironfolio/changesortorder/$item->nid/$next_item->nid/"; ?>">Down</a>
            <?php endif ?>
            <br />
            <a href="<?php echo $current_url_path . "node/$item->nid/edit/?destination=admin/ironfolio/$current_cat_id/"; ?>">Edit</a>
            <br />
            <a href="<?php echo $current_url_path . "node/$item->nid/delete/?destination=admin/ironfolio/$current_cat_id/"; ?>">Delete</a>
        </li>
    <?php endfor; ?>
    </ul>
</div>