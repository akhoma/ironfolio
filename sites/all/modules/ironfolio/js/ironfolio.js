(function (IronFolio, $) {

    var $cache = {};

    IronFolio.editForm = (function() {
        var init = function () {
            $cache.editForm = {};
            $cache.editForm.form = $('#form-ironfolio-edit-form');
            $cache.editForm.nodesSortOrderEl = $('#node_sort_order');
            $cache.editForm.nodesToDeleteEl = $('#nodes_to_delete');
            $cache.editForm.saveButtonEl = $('#folio-save');

            $cache.editForm.nodesSortOrderEl.val('');
            $cache.editForm.nodesToDeleteEl.val('');

            function initDeleteButton() {
                $('.folio-delete').each(function(index, value) {
                    $(this).click(function(){
                        var folioElement = $(this).parents('.folio-item');
                        var elementsToDelete = $cache.editForm.nodesToDeleteEl.val();
                        if (elementsToDelete) {
                            elementsToDelete = elementsToDelete + ',' + folioElement.attr('folio-item-id');
                        } else {
                            elementsToDelete = folioElement.attr('folio-item-id');
                        }
                        $cache.editForm.nodesToDeleteEl.val(elementsToDelete);
                        folioElement.hide('slow', function(){ this.remove(); });
                    });
                });
            };

            function initUpButton() {
                $('.folio-up').each(function(index, value) {
                    $(this).click(function(){
                        var folioElement = $(this).parents('.folio-item');
                        var prevElement = folioElement.prev();
                        folioElement.after(prevElement);
                    });
                });
            };

            function initDownButton() {
                $('.folio-down').each(function(index, value) {
                    $(this).click(function(){
                        var folioElement = $(this).parents('.folio-item');
                        var nextElement = folioElement.next();
                        nextElement.after(folioElement);
                    });
                });
            };

            function initSaveButton() {
                $cache.editForm.saveButtonEl.click(function(){
                    IronFolio.editForm.save();
                });
            };

            initDeleteButton();
            initUpButton();
            initDownButton();
            initSaveButton();
        };

        var save = function() {
            var folioItems = $('.folio-item');
            var sortedNodesIds = [];
            folioItems.each(function(index, value) {
                sortedNodesIds.push($(this).attr('folio-item-id'));
            });
            $cache.editForm.nodesSortOrderEl.val(sortedNodesIds.join());
            $cache.editForm.form.submit();
        }

        return {
            init : init,
            save : save
        }

    })()

}(window.IronFolio = window.IronFolio || {}, jQuery));