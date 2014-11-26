(function (IronFolio, $) {

    var $cache = {};

    IronFolio.orderForm = (function() {
        var init = function () {
            $cache.orderForm = {};
            $cache.orderForm.form = $('#form-ironfolio-edit-form');
            $cache.orderForm.formatEl = $('#edit-format');
            $cache.orderForm.formatsContainer = $('#folio-formats');

            function initFormats() {
                $cache.orderForm.formatsContainer.find('a').each(function(index, value) {
                    $(this).click(function(e){
                        e.preventDefault();
                        var formatText = ' ' + $(this).text() + ';';
                        var updatedFormatFieldValue = $cache.orderForm.formatEl.val() + formatText;
                        $cache.orderForm.formatEl.val(updatedFormatFieldValue);

                    });
                })
            };

            initFormats();
        };

        return {
            init : init
        }

    })()

}(window.IronFolio = window.IronFolio || {}, jQuery));